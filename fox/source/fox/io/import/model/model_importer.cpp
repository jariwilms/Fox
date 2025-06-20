#include "stdafx.hpp"

#include <fox/core/types/image/image.hpp>
#include "fox/io/io.hpp"
#include <fox/io/import/model/model_importer.hpp>

namespace fox::io
{
    void ModelImporter::init()
    {
        s_defaultAlbedoTexture = io::load<io::Asset::Texture2D>("textures/albedo.png");
        s_defaultNormalTexture = io::load<io::Asset::Texture2D>("textures/normal.png");
        s_defaultARMTexture    = io::load<io::Asset::Texture2D>("textures/arm.png");
    }

    std::shared_ptr<gfx::Model> ModelImporter::import(const std::filesystem::path& path)
    {
        auto const& get_assimp_texture = [](aiMaterial const* aiMaterial, TextureType type, const std::filesystem::path& path)
            {
                auto const& to_assimp_type = [](TextureType type)
                    {
                        switch (type)
                        {
                            case TextureType::Albedo:            return aiTextureType_DIFFUSE;
                            case TextureType::Normal:            return aiTextureType_NORMALS;
                            case TextureType::MetallicRoughness: return aiTextureType_METALNESS;

                            default: throw std::invalid_argument{ "Invalid texture type!" };
                        }
                    };
                auto        option         = std::optional<std::shared_ptr<gfx::Texture2D>>{};

                if (aiMaterial->GetTextureCount(aiTextureType_DIFFUSE))
                {
                    auto        aiTextureName = aiString{};
                    auto const& aiReturn      = aiMaterial->GetTexture(to_assimp_type(type), 0, &aiTextureName);

                    if (aiReturn == AI_SUCCESS) option.emplace(io::load<io::Asset::Texture2D>(path / aiTextureName.C_Str()));
                }

                return option;
            };

        auto        model         = std::make_shared<gfx::Model>();
        auto const& absolutePath  = fox::io::root / path;
        auto const& baseDirectory = absolutePath.parent_path();
        auto        importer      = Assimp::Importer{};
        auto const& importerFlags = fox::int32_t
        {
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
        };
        auto const* aiScene       = importer.ReadFile(absolutePath.string(), importerFlags);

        if (!aiScene)                                     throw std::runtime_error   { "Failed to read file!"             };
        if ( aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) throw std::invalid_argument{ "Scene structure is not complete!" };
        if (!aiScene->mRootNode)                          throw std::invalid_argument{ "Scene has not root node!"         };
        


        for (auto const* aiMesh     : std::span<const aiMesh    * const>{ aiScene->mMeshes   , aiScene->mNumMeshes    })
        {
            auto aiPositions    = std::span<const aiVector3D> { aiMesh->mVertices        , aiMesh->mNumVertices };
            auto aiNormals      = std::span<const aiVector3D> { aiMesh->mNormals         , aiMesh->mNumVertices };
            auto aiTangents     = std::span<const aiVector3D> { aiMesh->mTangents        , aiMesh->mNumVertices };
            auto aiTexCoords    = std::span<const aiVector3D> { aiMesh->mTextureCoords[0], aiMesh->mNumVertices };
            auto aiFaces        = std::span<const aiFace    > { aiMesh->mFaces           , aiMesh->mNumFaces    };

            auto positionsVector = aiPositions | std::views::transform([](auto const& position  ) { return fox::Vector3f{ position  .x, position  .y, position.z }; }) | std::ranges::to<std::vector>();
            auto normalsVector   = aiNormals   | std::views::transform([](auto const& normal    ) { return fox::Vector3f{ normal    .x, normal    .y, normal  .z }; }) | std::ranges::to<std::vector>();
            auto tangentsVector  = aiTangents  | std::views::transform([](auto const& tangent   ) { return fox::Vector3f{ tangent   .x, tangent   .y, tangent .z }; }) | std::ranges::to<std::vector>();
            auto texCoordsVector = aiTexCoords | std::views::transform([](auto const& coordinate) { return fox::Vector2f{ coordinate.x, coordinate.y             }; }) | std::ranges::to<std::vector>();
            auto indicesVector   = aiFaces     | std::views::transform([](auto const& face)       { return std::span<const fox::uint32_t>{ face.mIndices, face.mNumIndices }; })
                                               | std::views::join
                                               | std::ranges::to<std::vector>();


            
            auto layout2f = gfx::VertexLayout{};
            auto layout3f = gfx::VertexLayout{};

            layout2f.specify<fox::float32_t>(2u);
            layout3f.specify<fox::float32_t>(3u);

            auto vertexArray      = gfx::VertexArray                ::create();
            auto positionsBuffer  = gfx::VertexBuffer<fox::Vector3f>::create(positionsVector);
            auto normalsBuffer    = gfx::VertexBuffer<fox::Vector3f>::create(normalsVector);
            auto tangentsBuffer   = gfx::VertexBuffer<fox::Vector3f>::create(tangentsVector);
            auto texCoordsBuffer  = gfx::VertexBuffer<fox::Vector2f>::create(texCoordsVector);
            auto indicesBuffer    = gfx::IndexBuffer                ::create(indicesVector);

            vertexArray->tie(positionsBuffer, layout3f);
            vertexArray->tie(normalsBuffer  , layout3f);
            vertexArray->tie(tangentsBuffer , layout3f);
            vertexArray->tie(texCoordsBuffer, layout2f);
            vertexArray->tie(indicesBuffer            );



            model->meshes.emplace_back(std::move(std::make_shared<gfx::Mesh>(vertexArray)));
        }
        for (auto const* aiMaterial : std::span<const aiMaterial* const>{ aiScene->mMaterials, aiScene->mNumMaterials })
        {
            auto material    = std::make_shared<gfx::Material>();
            
            auto albedo      = get_assimp_texture(aiMaterial, TextureType::Albedo           , baseDirectory);
            auto normal      = get_assimp_texture(aiMaterial, TextureType::Normal           , baseDirectory);
            auto arm         = get_assimp_texture(aiMaterial, TextureType::MetallicRoughness, baseDirectory);

            material->albedo = albedo.value_or(s_defaultAlbedoTexture);
            material->normal = normal.value_or(s_defaultNormalTexture);
            material->arm    = arm   .value_or(s_defaultARMTexture);

            model->materials.emplace_back(std::move(material));
        }



        auto const& aiRootNode = *aiScene->mRootNode;
        model->nodes.emplace_back(gfx::Model::Node{});
        create_nodes(*model, 0, *aiScene, aiRootNode);



        return model;
    }
    void ModelImporter::create_nodes(gfx::Model& model, fox::uint32_t nodeIndex , const aiScene& asiScene, const aiNode& asiNode)
    {
        const auto& matrix = glm::transpose(*reinterpret_cast<const fox::Matrix4f*>(&asiNode.mTransformation));
        model.nodes.at(nodeIndex).localTransform = matrix;

        std::span<fox::uint32_t> asiNodeMeshIndices{ asiNode.mMeshes, asiNode.mNumMeshes };
        for (const auto& asiNodeMeshIndex : asiNodeMeshIndices)
        {
            const auto& childNodeIndex = static_cast<fox::uint32_t>(model.nodes.size());
                  auto& childNode      = model.nodes.emplace_back(gfx::Model::Node{});

            childNode.meshIndex     = asiNodeMeshIndex;
            childNode.materialIndex = asiScene.mMeshes[asiNodeMeshIndex]->mMaterialIndex;

            model.nodes.at(nodeIndex).children.emplace_back(childNodeIndex);
        }

        std::span<aiNode* const> asiChildren{ asiNode.mChildren, asiNode.mNumChildren };
        for (const auto& asiChild : asiChildren)
        {
            const auto& childNodeIndex = static_cast<fox::uint32_t>(model.nodes.size());
                  auto& child          = model.nodes.emplace_back(gfx::Model::Node{});

            model.nodes.at(nodeIndex).children.emplace_back(childNodeIndex);

            create_nodes(model, childNodeIndex, asiScene, *asiChild);
        }
    }
}
