#include "stdafx.hpp"

#include "ModelImporter.hpp"

#include "Fox/Rendering/Rendering.hpp"

namespace fox::io
{
	std::shared_ptr<gfx::Model> ModelImporter::import2(const std::filesystem::path& path)
	{
		Assimp::Importer importer{};

		const auto& fullPath      = "assets" / path;
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

        const auto* aiScene = importer.ReadFile(fullPath.string(), importerFlags);
        if (!aiScene)                                     throw std::runtime_error{ "Failed to read file!" };
        if ( aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) throw std::invalid_argument{ "Scene data structure is not complete!" };
        if (!aiScene->HasMeshes())                        throw std::invalid_argument{ "Model requires at least one mesh!" };



        auto model = std::make_shared<gfx::Model>();

        std::span<aiMesh* const> aiMeshes{ aiScene->mMeshes, aiScene->mNumMeshes };
        for (const auto* aiMesh : aiMeshes)
        {
            const auto& aiNumVertices = aiMesh->mNumVertices;
            const auto& aiNumFaces    = aiMesh->mNumFaces;

            std::vector<fox::Vector3f> positionsVector{};
            positionsVector.reserve(aiNumVertices);
            std::span<const aiVector3D> aiPositions{ aiMesh->mVertices, aiNumVertices };
            for (const auto& aiPosition : aiPositions)
            {
                positionsVector.emplace_back(aiPosition.x, aiPosition.y, aiPosition.z);
            }

            std::vector<fox::Vector3f> normalsVector{};
            normalsVector.reserve(aiNumVertices);
            std::span<const aiVector3D> aiNormals{ aiMesh->mNormals, aiNumVertices };
            for (const auto& aiNormal : aiNormals)
            {
                positionsVector.emplace_back(aiNormal.x, aiNormal.y, aiNormal.z);
            }

            std::vector<fox::Vector2f> texCoordsVector{};
            texCoordsVector.reserve(aiNumVertices);
            std::span<const aiVector3D> aiTexCoords{ aiMesh->mTextureCoords[0], aiNumVertices };
            for (const auto& aiTexCoord : aiTexCoords)
            {
                texCoordsVector.emplace_back(aiTexCoord.x, aiTexCoord.y);
            }

            std::vector<fox::uint32_t> indicesVector{};
            indicesVector.reserve(static_cast<fox::size_t>(aiNumFaces) * 3u);
            std::span<aiFace> aiFaces{ aiMesh->mFaces, aiNumFaces };
            for (const auto& aiFace : aiFaces)
            {
                std::span<fox::uint32_t> aiIndices{ aiFace.mIndices, aiFace.mNumIndices };

                for (const auto& aiIndex : aiIndices)
                {
                    indicesVector.emplace_back(aiIndex);
                }
            }



            const auto& layout2f = gfx::VertexLayout<float>({ 2u });
            const auto& layout3f = gfx::VertexLayout<float>({ 3u });

            auto vertexArray     = std::make_shared<gfx::VertexArray>();
            auto positionsBuffer = std::make_shared<gfx::VertexBuffer<gfx::api::Buffer::Access::Static, fox::Vector3f>>(positionsVector);
            auto normalsBuffer   = std::make_shared<gfx::VertexBuffer<gfx::api::Buffer::Access::Static, fox::Vector3f>>(normalsVector);
            auto texCoordsBuffer = std::make_shared<gfx::VertexBuffer<gfx::api::Buffer::Access::Static, fox::Vector2f>>(texCoordsVector);
            auto indicesBuffer   = std::make_shared<gfx::IndexBuffer<gfx::api::Buffer::Access::Static>>(indicesVector);

            vertexArray->tie(positionsBuffer, layout3f);
            vertexArray->tie(normalsBuffer,   layout3f);
            vertexArray->tie(texCoordsBuffer, layout2f);
            vertexArray->tie(indicesBuffer);



            auto mesh = std::make_shared<gfx::Mesh>(vertexArray);
            model->meshes.emplace_back(std::move(mesh));
        }

        std::span<aiMaterial*> aiMaterials{ aiScene->mMaterials, aiScene->mNumMaterials };
        for (const auto* aiMaterial : aiMaterials)
        {
            //aiMaterial->
        }

        return {};
	}
}
