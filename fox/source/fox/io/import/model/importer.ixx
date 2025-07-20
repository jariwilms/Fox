export module fox.io.model_importer;

import std;
import fox.core.image;
import fox.core.types;
import fox.core.utility;
import fox.io;
import fox.math;
import fox.rendering.layout;
import fox.rendering.material;
import fox.rendering.mesh;
import fox.rendering.model;
import fox.rendering.texture;
import fox.rendering.buffer;
import fox.rendering.vertex_array;
import vendor.assimp;

export namespace fox::io
{
    class ModelImporter
    {
    public:
        static void init()
        {
            defaultAlbedoTexture_ = io::load<io::Asset::Texture2D>("textures/albedo.png");
            defaultNormalTexture_ = io::load<io::Asset::Texture2D>("textures/normal.png");
            defaultARMTexture_    = io::load<io::Asset::Texture2D>("textures/arm.png");
        }

        static auto import2            (const std::filesystem::path& path) -> std::shared_ptr<gfx::Model>
        {
                  auto  model          = std::make_shared<gfx::Model>();
            const auto  modelPath      = fox::io::root / path;
            const auto  modelDirectory = modelPath.parent_path();

            const auto& aiScene        = assimp::load_scene(modelPath);



            std::ranges::for_each(std::span<const assimp::mesh    * const>{ aiScene.mMeshes   , aiScene.mNumMeshes    }, [&](const auto* aiMesh    )
                {
                    auto aiPositions     = std::span<const assimp::vector_3d>{ aiMesh->mVertices        , aiMesh->mNumVertices };
                    auto aiNormals       = std::span<const assimp::vector_3d>{ aiMesh->mNormals         , aiMesh->mNumVertices };
                    auto aiTangents      = std::span<const assimp::vector_3d>{ aiMesh->mTangents        , aiMesh->mNumVertices };
                    auto aiTexCoords     = std::span<const assimp::vector_3d>{ aiMesh->mTextureCoords[0], aiMesh->mNumVertices };
                    auto aiFaces         = std::span<const assimp::face     >{ aiMesh->mFaces           , aiMesh->mNumFaces    };

                    auto positionsVector = aiPositions | std::views::transform([](const auto& position  ) { return fox::Vector3f{ position.x, position.y, position.z };                              }) | std::ranges::to<std::vector>();
                    auto normalsVector   = aiNormals   | std::views::transform([](const auto& normal    ) { return fox::Vector3f{ normal  .x, normal  .y, normal  .z };                              }) | std::ranges::to<std::vector>();
                    auto tangentsVector  = aiTangents  | std::views::transform([](const auto& tangent   ) { return fox::Vector3f{ tangent .x, tangent .y, tangent .z };                              }) | std::ranges::to<std::vector>();
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
            std::ranges::for_each(std::span<const assimp::material* const>{ aiScene.mMaterials, aiScene.mNumMaterials }, [&](const auto* aiMaterial)
                {
                    auto material    = std::make_shared<gfx::Material>();
                    material->albedo = get_assimp_texture(modelDirectory, *aiMaterial, assimp::texture_type::albedo            ).value_or(defaultAlbedoTexture_);
                    material->normal = get_assimp_texture(modelDirectory, *aiMaterial, assimp::texture_type::normal            ).value_or(defaultNormalTexture_);
                    material->arm    = get_assimp_texture(modelDirectory, *aiMaterial, assimp::texture_type::metallic_roughness).value_or(defaultARMTexture_   );

                    model->materials.emplace_back(std::move(material));
                });



            const auto& aiRootNode = *aiScene.mRootNode;
            model->nodes.emplace_back(gfx::Model::Node{});

            create_nodes(model, fox::uint32_t{ 0u }, aiScene, aiRootNode);



            return model;
        }

    private:
        static auto get_assimp_texture(const std::filesystem::path& path, const assimp::material& aiMaterial, assimp::texture_type type) -> std::optional<std::shared_ptr<gfx::Texture2D>>
        {
            if (assimp::get_texture_count(aiMaterial, type))
            {
                if (auto result = assimp::get_texture(aiMaterial, type); result) return io::load<io::Asset::Texture2D>(path / result.value());
            }

            return std::nullopt;
        };
        static void create_nodes      (std::shared_ptr<gfx::Model> model, fox::size_t index, const assimp::scene& aiScene, const assimp::node& currentAiNode)
        {
            auto& currentNode = model->nodes.at(index);

            currentNode.transform = fox::Transform::from_matrix(math::transpose(std::bit_cast<fox::Matrix4f>(currentAiNode.mTransformation)));

            auto aiMeshes   = std::span<const fox::uint32_t>{ currentAiNode.mMeshes  , currentAiNode.mNumMeshes   };
            auto aiChildren = std::span<const assimp::node* const>{ currentAiNode.mChildren, currentAiNode.mNumChildren };

            std::ranges::for_each(aiMeshes  , [&](fox::uint32_t index)
                {
                    const auto  childNodeIndex = model->nodes.size();
                    auto& childNode      = model->nodes.emplace_back(gfx::Model::Node{});

                    childNode.mesh     = index;
                    childNode.material = aiScene.mMeshes[index]->mMaterialIndex;

                    model->nodes.at(index).children.emplace_back(childNodeIndex);
                });
            std::ranges::for_each(aiChildren, [&](const assimp::node* const node )
                {
                    const auto& childNodeIndex = model->nodes.size();
                    currentNode.children.emplace_back(childNodeIndex);

                    create_nodes(model, childNodeIndex, aiScene, *node);
                });
        }

        //static inline Assimp::Importer                importer_;
        static inline std::shared_ptr<gfx::Texture2D> defaultAlbedoTexture_;
        static inline std::shared_ptr<gfx::Texture2D> defaultNormalTexture_;
        static inline std::shared_ptr<gfx::Texture2D> defaultARMTexture_;
    };
}
