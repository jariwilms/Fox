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
            m_defaultPipeline = GraphicsAPI::create_plo("shaders/compiled/geometryvert.spv", "shaders/compiled/geometryfrag.spv");
            m_defaultMaterial = std::make_shared<DefaultMaterial>("Default", m_defaultPipeline);
            m_defaultMaterial->albedo = GraphicsAPI::create_tex(Texture::Format::RGBA, Texture::ColorDepth::_8bit, Vector2u{ 1, 1 }, Texture::Filter::Point, Texture::Wrapping::Repeat, Texture::Wrapping::Repeat, 1, true, Texture::Format::R, std::vector<byte>{ 0xFF });
            m_defaultMaterial->normal = GraphicsAPI::create_tex(Texture::Format::RGBA, Texture::ColorDepth::_8bit, Vector2u{ 1, 1 }, Texture::Filter::Point, Texture::Wrapping::Repeat, Texture::Wrapping::Repeat, 1, true, Texture::Format::RGB, std::vector<byte>{ 0x00, 0x00, 0xFF });

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

            const auto pFlags = 
                aiProcess_Triangulate        | 
                aiProcess_SortByPType        | 
                aiProcess_OptimizeGraph      | 
                aiProcess_OptimizeMeshes     | 
                aiProcess_GenNormals         |
                aiProcess_FixInfacingNormals | 
                aiProcess_CalcTangentSpace; 
            const auto aiScene = importer.ReadFile(absolutePath.string(), 0);
            if (!aiScene || !aiScene->mRootNode || aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) throw std::runtime_error{"Failed to load model!"};

            



            auto model = std::make_shared<Model>();





            //Create instance of every mesh and add to model
            if (!aiScene->HasMeshes()) throw std::runtime_error{ "Model requires at least one mesh!" };
            std::span<aiMesh* const> aiMeshes{ aiScene->mMeshes, aiScene->mNumMeshes };
            for (const auto& aiMesh : aiMeshes)
            {
                const auto& vertexCount = aiMesh->mNumVertices;

                std::vector<Vector3f> meshVertices{ vertexCount };
                std::span<const aiVector3D> aiMeshVertices{ aiMesh->mVertices, aiMesh->mNumVertices };
                for (auto index{ 0u }; const auto& aiMeshVertex : aiMeshVertices)
                {
                    meshVertices.at(index) = Vector3f{ aiMeshVertex.x, aiMeshVertex.y, aiMeshVertex.z };
                    ++index;
                }

                std::vector<Vector3f> meshNormals{ vertexCount };
                std::span<const aiVector3D> aiMeshNormals{ aiMesh->mNormals, aiMesh->mNumVertices };
                for (auto index{ 0u }; const auto& aiMeshNormal : aiMeshNormals)
                {
                    meshNormals.at(index) = Vector3f{ aiMeshNormal.x, aiMeshNormal.y, aiMeshNormal.z };
                    ++index;
                }

                std::vector<Vector2f> meshTexCoords{ vertexCount };
                std::span<const aiVector3D> aiMeshTexCoords{ aiMesh->mTextureCoords[0], aiMesh->mNumVertices };
                for (auto index{ 0u }; const auto& aiMeshTexCoord : aiMeshTexCoords)
                {
                    meshTexCoords.at(index) = Vector2f{ aiMeshTexCoord.x, aiMeshTexCoord.y };
                    ++index;
                }

                std::vector<unsigned int> meshIndices{};
                std::span<const aiFace> aiFaces{ aiMesh->mFaces, aiMesh->mNumFaces };
                for (const auto& aiFace : aiFaces)
                {
                    std::span<unsigned int> aiIndices{ aiFace.mIndices, aiFace.mNumIndices };
                    for (const auto& aiIndex : aiIndices)
                    {
                        meshIndices.emplace_back(aiIndex); //TODO: iterate once for array size, then use reserve as above?
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

                model->meshes.emplace_back(std::make_shared<Mesh>(meshVertexArray));
            }





            //Create instance of every material and add to model
            if (!aiScene->HasMaterials()) throw std::runtime_error{ "Model requires at least one material!" };

            TextureBlueprint textureBlueprint{};
            textureBlueprint.filter = Texture::Filter::Trilinear;
            std::span<aiMaterial*> aiMaterials{ aiScene->mMaterials, aiScene->mNumMaterials };
            for (auto index{ 0u }; const auto & aiMaterial : aiMaterials)
            {
                //auto material = std::make_shared<DefaultMaterial>(std::string{ "Material" } + std::to_string(index), m_defaultPipeline);
                auto material = std::make_shared<DefaultMaterial>(*m_defaultMaterial);

                if (aiString aiMaterialName; aiMaterial->Get(AI_MATKEY_NAME, aiMaterialName) == aiReturn_SUCCESS && aiMaterialName.length > 0) material->name = aiMaterialName.C_Str();
                else material->name = "Default";

                if (aiColor3D aiBaseColor; aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiBaseColor) == aiReturn_SUCCESS) material->color = Vector4f{ aiBaseColor.r, aiBaseColor.g, aiBaseColor.b, 1.0f };

                if (aiString aiMaterialDiffuse; aiMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), aiMaterialDiffuse) == aiReturn_SUCCESS)
                {
                    const auto aiMaterialDiffuseImage = std::make_shared<Image>(baseDirectory / aiMaterialDiffuse.C_Str());
                    const auto aiMaterialDiffuseTexture = textureBlueprint.build(aiMaterialDiffuseImage, 1u, true);
                    material->albedo = aiMaterialDiffuseTexture;
                }

                if (aiString aiMaterialNormal; aiMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), aiMaterialNormal) == aiReturn_SUCCESS)
                {
                    const auto aiMaterialNormalImage = std::make_shared<Image>(baseDirectory / aiMaterialNormal.C_Str());
                    const auto aiMaterialNormalTexture = textureBlueprint.build(aiMaterialNormalImage);
                    material->normal = aiMaterialNormalTexture;
                }

                model->materials.emplace_back(material);
            }



            //Assimp may have multiple meshes per node => Create node for every mesh
            std::queue<Model::Node*> nodeQueue{};
            nodeQueue.push(model->rootNode.get());

            std::queue<aiNode*> aiNodeQueue{};
            aiNodeQueue.push(aiScene->mRootNode);

            while (!aiNodeQueue.empty())
            {
                //Get front node of our and assimp's queue
                auto& frontNode = nodeQueue.front();
                const auto& aiFrontNode = aiNodeQueue.front();

                //The total amount of children is equal to max(current aiFrontNode's number of meshes - 1, 0) and the amount of child nodes it has
                std::span<aiNode*> aiFrontNodeChildren{ aiFrontNode->mChildren, aiFrontNode->mNumChildren };
                const auto totalChildren = aiFrontNode->mNumMeshes == 1 ? 0 : aiFrontNodeChildren.size() + aiFrontNode->mNumMeshes;
                frontNode->children.reserve(totalChildren);

                //Create a child Node for each mesh after the first, but do not add them to the queue
                const auto& aiFrontNodeTransform = *reinterpret_cast<Matrix4f*>(&aiFrontNode->mTransformation);
                frontNode->localTransform = aiFrontNodeTransform;
                frontNode->cameraIndex = std::nullopt;
                if (aiFrontNode->mNumMeshes)
                {
                    if (aiFrontNode->mNumMeshes == 1)
                    {
                        const auto& aiFrontNodeFirstMeshIndex = aiFrontNode->mMeshes[0];
                        const auto& aiFrontNodeFirstMaterialIndex = aiScene->mMeshes[aiFrontNodeFirstMeshIndex]->mMaterialIndex;
                        frontNode->meshPrimitive = Model::Node::Primitive{ aiFrontNodeFirstMeshIndex, aiFrontNodeFirstMaterialIndex };
                    }
                    else
                    {
                        for (auto i{ 0u }; i < aiFrontNode->mNumMeshes; ++i)
                        {
                            const auto& aiFrontNodeMeshIndex = aiFrontNode->mMeshes[i];
                            const auto& aiFrontNodeMaterialIndex = aiScene->mMeshes[aiFrontNodeMeshIndex]->mMaterialIndex;
                            frontNode->children.emplace_back(Matrix4f{ 1.0f }, std::nullopt, Model::Node::Primitive{ aiFrontNodeMeshIndex, aiFrontNodeMaterialIndex });
                        }
                    }
                }

                //Queue every child of the current aiFrontNode
                for (const auto& aiFrontNodeChild : aiFrontNodeChildren)
                {
                    aiNodeQueue.push(aiFrontNodeChild);
                    auto& modelNode = frontNode->children.emplace_back();
                    nodeQueue.push(&modelNode);
                }

                nodeQueue.pop();
                aiNodeQueue.pop();
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

        static inline std::shared_ptr<Pipeline> m_defaultPipeline{};
        static inline std::shared_ptr<DefaultMaterial> m_defaultMaterial{};
        static inline std::shared_ptr<VertexLayout> m_layout3f{};
        static inline std::shared_ptr<VertexLayout> m_layout2f{};
    };
}
