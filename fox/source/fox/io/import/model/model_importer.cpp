#include <stdafx.hpp>

#include <fox/core/image/image.hpp>
#include <fox/io/import/model/model_importer.hpp>
#include <fox/io/io.hpp>

namespace fox::io
{
    void ModelImporter::init()
    {
        defaultAlbedoTexture_ = io::load<io::Asset::Texture2D>("textures/albedo.png");
        defaultNormalTexture_ = io::load<io::Asset::Texture2D>("textures/normal.png");
        defaultARMTexture_    = io::load<io::Asset::Texture2D>("textures/arm.png");
    }

    auto ModelImporter::import            (const std::filesystem::path& path) -> std::shared_ptr<gfx::Model>
    {
              auto  model          = std::make_shared<gfx::Model>();
        const auto  modelPath      = fox::io::root / path;
        const auto  modelDirectory = modelPath.parent_path();
        
        const auto& aiScene        = load_scene(modelPath);
        


        std::ranges::for_each(std::span<const aiMesh    * const>{ aiScene.mMeshes   , aiScene.mNumMeshes    }, [&](const auto* aiMesh    )
            {
                auto aiPositions     = std::span<const aiVector3D>{ aiMesh->mVertices        , aiMesh->mNumVertices };
                auto aiNormals       = std::span<const aiVector3D>{ aiMesh->mNormals         , aiMesh->mNumVertices };
                auto aiTangents      = std::span<const aiVector3D>{ aiMesh->mTangents        , aiMesh->mNumVertices };
                auto aiTexCoords     = std::span<const aiVector3D>{ aiMesh->mTextureCoords[0], aiMesh->mNumVertices };
                auto aiFaces         = std::span<const aiFace    >{ aiMesh->mFaces           , aiMesh->mNumFaces    };

                auto positionsVector = aiPositions | std::views::transform([](const auto& position  ) { return std::bit_cast<fox::Vector3f>(position);                            }) | std::ranges::to<std::vector>();
                auto normalsVector   = aiNormals   | std::views::transform([](const auto& normal    ) { return std::bit_cast<fox::Vector3f>(normal  );                            }) | std::ranges::to<std::vector>();
                auto tangentsVector  = aiTangents  | std::views::transform([](const auto& tangent   ) { return std::bit_cast<fox::Vector3f>(tangent );                            }) | std::ranges::to<std::vector>();
                auto texCoordsVector = aiTexCoords | std::views::transform([](const auto& coordinate) { return fox::Vector2f{ coordinate.x, coordinate.y };                       }) | std::ranges::to<std::vector>();
                auto indicesVector   = aiFaces     | std::views::transform([](const auto& face      ) { return std::span<const fox::uint32_t>{ face.mIndices, face.mNumIndices }; })
                                                   | std::views::join
                                                   | std::ranges::to<std::vector>();
            
                auto layout2f        = gfx::layout_t<gfx::attribute_t<fox::float32_t, 2u>>{};
                auto layout3f        = gfx::layout_t<gfx::attribute_t<fox::float32_t, 3u>>{};

                auto vertexArray     = gfx::VertexArray                ::create();
                auto positionsBuffer = gfx::VertexBuffer<fox::Vector3f>::create(positionsVector);
                auto normalsBuffer   = gfx::VertexBuffer<fox::Vector3f>::create(normalsVector);
                auto tangentsBuffer  = gfx::VertexBuffer<fox::Vector3f>::create(tangentsVector);
                auto texCoordsBuffer = gfx::VertexBuffer<fox::Vector2f>::create(texCoordsVector);
                auto indicesBuffer   = gfx::IndexBuffer                ::create(indicesVector);

                vertexArray->tie(positionsBuffer, layout3f);
                vertexArray->tie(normalsBuffer  , layout3f);
                vertexArray->tie(tangentsBuffer , layout3f);
                vertexArray->tie(texCoordsBuffer, layout2f);
                vertexArray->tie(indicesBuffer            );

                model->meshes.emplace_back(std::move(std::make_shared<gfx::Mesh>(vertexArray)));
            });
        std::ranges::for_each(std::span<const aiMaterial* const>{ aiScene.mMaterials, aiScene.mNumMaterials }, [&](const auto* aiMaterial)
            {
                auto material    = std::make_shared<gfx::Material>();
                material->albedo = get_assimp_texture(modelDirectory, *aiMaterial, TextureType::Albedo           ).value_or(defaultAlbedoTexture_);
                material->normal = get_assimp_texture(modelDirectory, *aiMaterial, TextureType::Normal           ).value_or(defaultNormalTexture_);
                material->arm    = get_assimp_texture(modelDirectory, *aiMaterial, TextureType::MetallicRoughness).value_or(defaultARMTexture_   );

                model->materials.emplace_back(std::move(material));
            });



        const auto& aiRootNode = *aiScene.mRootNode;
        model->nodes.emplace_back(gfx::Model::Node{});
        model->root = fox::uint32_t{ 0u };

        create_nodes(model, fox::uint32_t{ 0u }, aiScene, aiRootNode);



        return model;
    }
    auto ModelImporter::load_scene        (const std::filesystem::path& path) -> const aiScene&
    {
        const auto* aiScene = importer_.ReadFile(path.string(), 
            aiProcess_CalcTangentSpace      | //Calculate tangents and bitangents
            aiProcess_FindInvalidData       | //Removes/fixes invalid mesh data
            aiProcess_FixInfacingNormals    | //Inverts inwards facing normals
            aiProcess_GenBoundingBoxes      | //Generates AABB's for each mesh
            aiProcess_GenSmoothNormals      | //Generate normals for all faces of all meshes
            aiProcess_GenUVCoords           | //Converts non UV-mappings to texture coordinates channels
            aiProcess_ImproveCacheLocality  | //Reorder triangles for better vertex cache locality
            aiProcess_JoinIdenticalVertices | //Let each mesh contain unique vertices
            aiProcess_OptimizeGraph         | //Nodes without animations, bones etc. are collapsed and joined
            aiProcess_OptimizeMeshes        | //Reduces the number of meshes
            aiProcess_SortByPType           | //Split meshes with >1 primitive type into submeshes
            aiProcess_SplitLargeMeshes      | //Split up larges meshes into smaller meshes
            aiProcess_TransformUVCoords     | //Applies per-texture UV transformations
            aiProcess_Triangulate             //Split up faces with >3 indices into triangles
            );

        if (!aiScene)                                     throw std::runtime_error{ "Failed to create scene!" };
        if ( aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) throw std::runtime_error{ "Scene is not complete!"  };
        if (!aiScene->mRootNode)                          throw std::runtime_error{ "Scene has no root node!" };

        return *aiScene;
    }
    auto ModelImporter::get_assimp_texture(const std::filesystem::path& path, const aiMaterial& aiMaterial, TextureType type) -> std::optional<std::shared_ptr<gfx::Texture2D>>
        {
            auto to_assimp_type = [](TextureType type)
                {
                    switch (type)
                    {
                        case TextureType::Albedo:            return aiTextureType_DIFFUSE;
                        case TextureType::Normal:            return aiTextureType_NORMALS;
                        case TextureType::MetallicRoughness: return aiTextureType_METALNESS;

                        default: throw std::invalid_argument{ "Invalid texture type!" };
                    }
                };

            auto aiTextureType = to_assimp_type(type);
            if (fox::compare<std::greater>(aiMaterial.GetTextureCount(aiTextureType), fox::uint32_t{ 0u }))
            {
                auto aiTextureName = aiString{};
                auto aiReturn      = aiMaterial.GetTexture(aiTextureType, fox::uint32_t{ 0u }, &aiTextureName);

                if (aiReturn == AI_SUCCESS) return io::load<io::Asset::Texture2D>(path / aiTextureName.C_Str());
            }

            return {};
        };
    void ModelImporter::create_nodes      (std::shared_ptr<gfx::Model> model, fox::size_t index, const aiScene& aiScene, const aiNode& currentAiNode)
    {
        auto& currentNode = model->nodes.at(index);
        currentNode.transform = fox::Transform::from_matrix(math::transpose(std::bit_cast<const fox::Matrix4f>(currentAiNode.mTransformation)));

        auto aiMeshes   = std::span<const fox::uint32_t>{ currentAiNode.mMeshes  , currentAiNode.mNumMeshes   };
        auto aiChildren = std::span<const aiNode* const>{ currentAiNode.mChildren, currentAiNode.mNumChildren };

        std::ranges::for_each(aiMeshes  , [&](fox::uint32_t index)
            {
                const auto  childNodeIndex = model->nodes.size();
                      auto& childNode      = model->nodes.emplace_back(gfx::Model::Node{});

                childNode.mesh     = index;
                childNode.material = aiScene.mMeshes[index]->mMaterialIndex;

                model->nodes.at(index).children.emplace_back(childNodeIndex);
            });
        std::ranges::for_each(aiChildren, [&](const aiNode* const node )
            {
                const auto& childNodeIndex = model->nodes.size();
                      auto& child          = model->nodes.emplace_back(gfx::Model::Node{});

                currentNode.children.emplace_back(childNodeIndex);

                create_nodes(model, childNodeIndex, aiScene, *node);
            });
    }
}
