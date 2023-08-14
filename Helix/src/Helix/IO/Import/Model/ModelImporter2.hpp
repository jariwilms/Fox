#pragma once

#include "stdafx.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Helix/IO/IO.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Model/Model.hpp"

namespace hlx
{
    class ModelImporter2
    {
    public:

        static void init()
        {
            const auto pipeline = GraphicsAPI::create_plo("shaders/compiled/geometryvert.spv", "shaders/compiled/geometryfrag.spv");
            m_defaultMaterial = std::make_shared<DefaultMaterial>("Default", pipeline);
            m_defaultMaterial->albedo = GraphicsAPI::create_tex(Texture::Format::RGBA, Texture::ColorDepth::_8Bit, Vector2u{ 1, 1 }, Texture::Filter::Point, Texture::Wrapping::Repeat, Texture::Wrapping::Repeat, 1, true, Texture::Format::R, std::vector<byte>{ 0xFF });
            m_defaultMaterial->normal = GraphicsAPI::create_tex(Texture::Format::RGBA, Texture::ColorDepth::_8Bit, Vector2u{ 1, 1 }, Texture::Filter::Point, Texture::Wrapping::Repeat, Texture::Wrapping::Repeat, 1, true, Texture::Format::RGB, std::vector<byte>{ 0x00, 0x00, 0xFF });

            m_layout3f = std::make_shared<VertexLayout>();
            m_layout3f->specify<float>(3);

            m_layout2f = std::make_shared<VertexLayout>();
            m_layout2f->specify<float>(2);
        }

        static std::shared_ptr<Model> import(const std::filesystem::path& modelPath)
        {
            Assimp::Importer importer{};

            const auto absolutePath = IO::root() / modelPath.string();
            const auto baseDirectory = absolutePath.parent_path();

            const auto pFlags = aiProcess_Triangulate | aiProcess_SortByPType | aiProcess_OptimizeGraph | aiProcess_OptimizeMeshes | aiProcess_GenNormals | aiProcess_FixInfacingNormals | aiProcess_CalcTangentSpace;
            const auto aiScene = importer.ReadFile(absolutePath.string(), pFlags);
            if (!aiScene || !aiScene->mRootNode || aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) throw std::runtime_error{"Failed to load model!"};



            auto model = std::make_shared<Model>();
            model->meshes = get_meshes(aiScene);
            model->materials = get_materials(aiScene, baseDirectory);
            for (auto i{ 0u }; i < aiScene->mNumMeshes; ++i)
            {
                model->materialMap.emplace(model->meshes[i], model->materials[aiScene->mMeshes[i]->mMaterialIndex]);
            }



            return model;
        }

    private:
        static std::vector<std::shared_ptr<Mesh>> get_meshes(const aiScene* aiScene)
        {
            std::vector<std::shared_ptr<Mesh>> meshes{};

            if (!aiScene->mNumMeshes) throw std::runtime_error{ "Model has no meshes!" };
            for (auto i{ 0u }; i < aiScene->mNumMeshes; ++i)
            {
                const auto& aiMesh = aiScene->mMeshes[i];



                std::vector<Vector3f> meshVertices{};
                std::vector<Vector3f> meshNormals{};
                std::vector<Vector2f> meshTexCoords{};
                for (auto j{ 0u }; j < aiMesh->mNumVertices; ++j)
                {
                    const auto& meshVertex = aiMesh->mVertices[j];
                    meshVertices.emplace_back(meshVertex.x, meshVertex.y, meshVertex.z);

                    const auto& meshNormal = aiMesh->mNormals[j];
                    meshNormals.emplace_back(meshNormal.x, meshNormal.y, meshNormal.z);

                    const auto& meshTexCoord = aiMesh->mTextureCoords[0][j];
                    meshTexCoords.emplace_back(Vector2f{ meshTexCoord.x, meshTexCoord.y });
                }

                std::vector<unsigned int> meshIndices{};
                for (auto j{ 0u }; j < aiMesh->mNumFaces; ++j)
                {
                    const auto& face = aiMesh->mFaces[j];

                    for (auto k{ 0u }; k < face.mNumIndices; ++k)
                    {
                        meshIndices.emplace_back(face.mIndices[k]);
                    }
                }



                const auto meshVertexArray = GraphicsAPI::create_vao();
                const auto meshVertexBuffer = GraphicsAPI::create_vbo<Vector3f>(meshVertices); //TODO: vbo move impl
                const auto meshNormalsBuffer = GraphicsAPI::create_vbo<Vector3f>(meshNormals);
                const auto meshTexCoordsBuffer = GraphicsAPI::create_vbo<Vector2f>(meshTexCoords);
                const auto meshIndicesBuffer = GraphicsAPI::create_ibo(meshIndices);

                meshVertexArray->tie(meshVertexBuffer, m_layout3f);
                meshVertexArray->tie(meshNormalsBuffer, m_layout3f);
                meshVertexArray->tie(meshTexCoordsBuffer, m_layout2f);
                meshVertexArray->tie(meshIndicesBuffer);

                meshes.emplace_back(std::make_shared<Mesh>(meshVertexArray));
            }

            return meshes;
        }
        static std::vector<std::shared_ptr<DefaultMaterial>> get_materials(const aiScene* aiScene, const std::filesystem::path& baseDirectory)
        {
            if (!aiScene->mNumMaterials) return { m_defaultMaterial };

            std::vector<std::shared_ptr<DefaultMaterial>> materials{};
            TextureBlueprint textureBlueprint{};
            textureBlueprint.filter = Texture::Filter::Trilinear;

            for (auto i{ 0u }; i < aiScene->mNumMaterials; ++i)
            {
                std::shared_ptr<DefaultMaterial> material = m_defaultMaterial;
                const auto& aiMaterial = *aiScene->mMaterials[i];
                aiString materialName{};

                aiMaterial.Get(AI_MATKEY_NAME, materialName);
                if (materialName.length)
                {
                    aiString materialDiffuse{};
                    aiString materialNormal{};

                    material->name = materialName.C_Str();

                    aiMaterial.Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), materialDiffuse);
                    if (materialDiffuse.length)
                    {
                        const auto diffuseImage = std::make_shared<Image>(baseDirectory / materialDiffuse.C_Str());
                        const auto diffuseTexture = textureBlueprint.build(diffuseImage, 1u, true);
                        material->albedo = diffuseTexture;
                    }

                    aiMaterial.Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), materialNormal);
                    if (materialNormal.length)
                    {
                        const auto normalImage = std::make_shared<Image>(baseDirectory / materialNormal.C_Str());
                        const auto normalTexture = textureBlueprint.build(normalImage);
                        material->normal = normalTexture;
                    }

                    materials.emplace_back(std::move(material));
                }
            }

            return materials;
        }

        static inline std::shared_ptr<DefaultMaterial> m_defaultMaterial{};
        static inline std::shared_ptr<VertexLayout> m_layout3f{};
        static inline std::shared_ptr<VertexLayout> m_layout2f{};
    };
}
