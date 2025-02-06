#include "stdafx.hpp"

#include "ModelImporter.hpp"

#include "Fox/Rendering/Rendering.hpp"
#include "Fox/Core/Library/Image/Image.hpp"

namespace fox::io
{
    void ModelImporter::init()
    {
        s_defaultAlbedoTexture = gfx::api::texture_from_file("textures/albedo.png");
        s_defaultNormalTexture = gfx::api::texture_from_file("textures/normal.png");
        s_defaultARMTexture    = gfx::api::texture_from_file("textures/arm.png");
    }

    std::shared_ptr<gfx::Model> ModelImporter::import2(const std::filesystem::path& path)
	{
		Assimp::Importer asiImporter{};

        const auto& fullPath      = path.lexically_normal();
		const auto& baseDirectory = fullPath.parent_path();

		const auto& importerFlags =
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
            aiProcess_Triangulate           ; //Split up faces with >3 indices into triangles

        const auto* asiScene = asiImporter.ReadFile("assets/" + fullPath.string(), importerFlags);
        if (!asiScene)                                     throw std::runtime_error{ "Failed to read file!" };
        if ( asiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) throw std::invalid_argument{ "Scene data structure is not complete!" };
        if (!asiScene->mRootNode)                          throw std::invalid_argument{ "Scene requires at least one node!" };
        if (!asiScene->HasMeshes())                        throw std::invalid_argument{ "Model requires at least one mesh!" };



        auto model = std::make_shared<gfx::Model>();

        

        std::span<aiMesh* const> asiMeshes{ asiScene->mMeshes, asiScene->mNumMeshes };
        for (const auto* asiMesh : asiMeshes)
        {
            const auto& asiNumVertices = asiMesh->mNumVertices;
            const auto& asiNumFaces    = asiMesh->mNumFaces;

            std::vector<fox::Vector3f> positionsVector{};
            positionsVector.reserve(asiNumVertices);
            std::span<const aiVector3D> asiPositions{ asiMesh->mVertices, asiNumVertices };
            for (const auto& asiPosition : asiPositions)
            {
                positionsVector.emplace_back(asiPosition.x, asiPosition.y, asiPosition.z);
            }

            std::vector<fox::Vector3f> normalsVector{};
            normalsVector.reserve(asiNumVertices);
            std::span<const aiVector3D> asiNormals{ asiMesh->mNormals, asiNumVertices };
            for (const auto& asiNormal : asiNormals)
            {
                normalsVector.emplace_back(asiNormal.x, asiNormal.y, asiNormal.z);
            }

            std::vector<fox::Vector3f> tangentsVector{};
            tangentsVector.reserve(asiNumVertices);
            std::span<const aiVector3D> asiTangents{ asiMesh->mTangents, asiMesh->mNumVertices };
            for (const auto& asiTangent : asiTangents)
            {
                tangentsVector.emplace_back(asiTangent.x, asiTangent.y, asiTangent.z);
            }

            std::vector<fox::Vector2f> texCoordsVector{};
            texCoordsVector.reserve(asiNumVertices);
            std::span<const aiVector3D> asiTexCoords{ asiMesh->mTextureCoords[0], asiNumVertices };
            for (const auto& asiTexCoord : asiTexCoords)
            {
                texCoordsVector.emplace_back(asiTexCoord.x, asiTexCoord.y);
            }

            std::vector<fox::uint32_t> indicesVector{};
            indicesVector.reserve(static_cast<fox::size_t>(asiNumFaces) * 3u);
            std::span<aiFace> asiFaces{ asiMesh->mFaces, asiNumFaces };
            for (const auto& asiFace : asiFaces)
            {
                std::span<fox::uint32_t> aiIndices{ asiFace.mIndices, asiFace.mNumIndices };

                for (const auto& aiIndex : aiIndices)
                {
                    indicesVector.emplace_back(aiIndex);
                }
            }



            gfx::VertexLayout layout2f{};
            gfx::VertexLayout layout3f{};

            layout2f.specify<fox::float32_t>(2);
            layout3f.specify<fox::float32_t>(3);

            auto vertexArray      = std::make_shared<gfx::VertexArray>();
            auto positionsBuffer  = std::make_shared<gfx::VertexBuffer<fox::Vector3f>>(positionsVector);
            auto normalsBuffer    = std::make_shared<gfx::VertexBuffer<fox::Vector3f>>(normalsVector);
            auto tangentsBuffer   = std::make_shared<gfx::VertexBuffer<fox::Vector3f>>(tangentsVector);
            auto texCoordsBuffer  = std::make_shared<gfx::VertexBuffer<fox::Vector2f>>(texCoordsVector);
            auto indicesBuffer    = std::make_shared<gfx::IndexBuffer>(indicesVector);

            vertexArray->tie(positionsBuffer,  layout3f);
            vertexArray->tie(normalsBuffer,    layout3f);
            vertexArray->tie(tangentsBuffer,   layout3f);
            vertexArray->tie(texCoordsBuffer,  layout2f);
            vertexArray->tie(indicesBuffer);



            auto mesh = std::make_shared<gfx::Mesh>(vertexArray);
            model->meshes.emplace_back(std::move(mesh));
        }

        std::span<aiMaterial* const> aiMaterials{ asiScene->mMaterials, asiScene->mNumMaterials };
        for (const auto* asiMaterial : aiMaterials)
        {
            auto material = std::make_shared<gfx::Material>();

            auto albedoTextureOpt = get_assimp_texture(asiMaterial, TextureType::Albedo, baseDirectory);
            material->albedo = albedoTextureOpt.value_or(s_defaultAlbedoTexture);

            auto normalTextureOpt = get_assimp_texture(asiMaterial, TextureType::Normal, baseDirectory);
            material->normal = normalTextureOpt.value_or(s_defaultNormalTexture);

            auto ARMTextureOpt = get_assimp_texture(asiMaterial, TextureType::MetallicRoughness, baseDirectory);
            material->arm = ARMTextureOpt.value_or(s_defaultARMTexture);

            model->materials.emplace_back(std::move(material));
        }



        const auto& asiRootNode = *asiScene->mRootNode;
        model->nodes.emplace_back(gfx::Model::Node{});
        create_nodes(*model, 0, *asiScene, asiRootNode);



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
    auto ModelImporter::to_assimp_type(TextureType type)
    {
        switch (type)
        {
            case TextureType::Albedo:            return aiTextureType_DIFFUSE;
            case TextureType::Normal:            return aiTextureType_NORMALS;
            case TextureType::MetallicRoughness: return aiTextureType_METALNESS;

            default: throw std::invalid_argument{ "Invalid texture type!" };
        }
    }
    std::optional<std::shared_ptr<gfx::Texture2D>> ModelImporter::get_assimp_texture(const aiMaterial* aiMaterial, TextureType type, const std::filesystem::path& path)
    {
        std::optional<std::shared_ptr<gfx::Texture2D>> textureOpt{};

        if (aiMaterial->GetTextureCount(aiTextureType_DIFFUSE))
        {
            aiString aiTextureName{};
            const auto& aiReturn = aiMaterial->GetTexture(to_assimp_type(type), 0, &aiTextureName);

            if (aiReturn == AI_SUCCESS) textureOpt.emplace(gfx::api::texture_from_file(path / aiTextureName.C_Str()));
        }

        return textureOpt;
    }
}
