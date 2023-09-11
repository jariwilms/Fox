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
    class ModelImporter
    {
    public:

        static void init()
        {
            m_defaultMaterial = std::make_shared<Material>("Default");
            m_defaultMaterial->albedoMap   = GraphicsAPI::create_tex(Texture::Format::RGBA, Texture::ColorDepth::_8bit, Vector2u{ 1, 1 }, Texture::Filter::Point, Texture::Wrapping::Repeat, Texture::Wrapping::Repeat, 1, true, Texture::Format::RGBA, std::vector<byte>{ 0xFF, 0xFF, 0xFF, 0xFF });
            m_defaultMaterial->normalMap   = GraphicsAPI::create_tex(Texture::Format::RGB,  Texture::ColorDepth::_8bit, Vector2u{ 1, 1 }, Texture::Filter::Point, Texture::Wrapping::Repeat, Texture::Wrapping::Repeat, 1, true, Texture::Format::RGB,  std::vector<byte>{ 0x80, 0x80, 0xFF });
            m_defaultMaterial->armMap      = GraphicsAPI::create_tex(Texture::Format::RGB,  Texture::ColorDepth::_8bit, Vector2u{ 1, 1 }, Texture::Filter::Point, Texture::Wrapping::Repeat, Texture::Wrapping::Repeat, 1, true, Texture::Format::RGB,  std::vector<byte>{ 0x00, 0x00, 0x00 });
            m_defaultMaterial->emissionMap = GraphicsAPI::create_tex(Texture::Format::RGB, Texture::ColorDepth::_8bit, Vector2u{ 1, 1 }, Texture::Filter::Point, Texture::Wrapping::Repeat, Texture::Wrapping::Repeat, 1, true, Texture::Format::RGB, std::vector<byte>{ 0x00, 0x00, 0x00 });

            m_layout3f = std::make_shared<VertexLayout>();
            m_layout2f = std::make_shared<VertexLayout>();

            m_layout3f->specify<float>(3);
            m_layout2f->specify<float>(2);
        }

        static std::shared_ptr<Model> import(const std::filesystem::path& modelPath)
        {
            Assimp::Importer importer{};

            const auto absolutePath = IO::root() / modelPath.string();
            const auto baseDirectory = absolutePath.parent_path();



            //Presets: aiProcessPreset_TargetRealtime_Fast or aiProcessPreset_TargetRealtime_Quality
            const auto pFlags = //aiProcessPreset_TargetRealtime_Fast;
                aiProcess_FindInvalidData       | //Removes/fixes invalid mesh data
                aiProcess_JoinIdenticalVertices | //Let each mesh contain unique vertices
                aiProcess_SplitLargeMeshes      | //Split up larges meshes into smaller meshes
                aiProcess_ImproveCacheLocality  | //Reorder triangles for better vertex cache locality
                aiProcess_Triangulate           | //Split up faces with >3 indices into triangles
                aiProcess_SortByPType           | //Split meshes with >1 primitive type into submeshes
                aiProcess_GenUVCoords           | //Converts non UV-mappings to texture coordinates channels
                aiProcess_TransformUVCoords     | //Applies per-texture UV transformations
                aiProcess_GenSmoothNormals      | //Generate normals for all faces of all meshes
                aiProcess_CalcTangentSpace      | //Calculate tangents and bitangents
                aiProcess_FixInfacingNormals    | //Inverts inwards facing normals
                aiProcess_OptimizeMeshes        | //Reduces the number of meshes
                aiProcess_OptimizeGraph         | //Nodes without animations, bones etc. are collapsed and joined
                aiProcess_GenBoundingBoxes      ; //Generates AABB's for each mesh

            //For left handed coordinate systems (=> aiProcess_ConvertLeftHanded)
            //aiProcess_MakeLeftHanded   | 
            //aiProcess_FlipUVs          | 
            //aiProcess_FlipWindingOrder ;

            const auto aiScene = importer.ReadFile(absolutePath.string(), pFlags);
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
                auto material = std::make_shared<Material>(*m_defaultMaterial);

                if (aiString aiMaterialName{}; aiMaterial->Get(AI_MATKEY_NAME, aiMaterialName) == aiReturn_SUCCESS && aiMaterialName.length > 0) material->name = aiMaterialName.C_Str();
                else material->name = "Default";

                if (aiColor3D aiBaseColor{}; aiMaterial->Get(AI_MATKEY_BASE_COLOR, aiBaseColor) == aiReturn_SUCCESS)
                {
                    material->color = Vector4f{ aiBaseColor.r, aiBaseColor.g, aiBaseColor.b, 1.0f };
                }
                if (aiString aiAlbedoTexturePath{}; aiMaterial->GetTexture(AI_MATKEY_BASE_COLOR_TEXTURE, &aiAlbedoTexturePath) == aiReturn_SUCCESS)
                {
                    const auto albedoImage   = std::make_shared<Image>(baseDirectory / aiAlbedoTexturePath.C_Str());
                    const auto albedoTexture = textureBlueprint.build(albedoImage, 4u, true);
                    material->albedoMap = albedoTexture;
                }
                if (aiString aiNormalTexturePath{}; aiMaterial->GetTexture(aiTextureType_NORMALS, 0, &aiNormalTexturePath) == aiReturn_SUCCESS)
                {
                    const auto normalImage = std::make_shared<Image>(baseDirectory / aiNormalTexturePath.C_Str());
                    const auto normalTexture = textureBlueprint.build(normalImage, 4u, false);
                    material->normalMap = normalTexture;
                }
                if (ai_real aiRoughnessFactor{}; aiMaterial->Get(AI_MATKEY_ROUGHNESS_FACTOR, aiRoughnessFactor) == aiReturn_SUCCESS)
                {
                    material->roughness = aiRoughnessFactor;
                }
                if (ai_real aiMetallicFactor{}; aiMaterial->Get(AI_MATKEY_METALLIC_FACTOR, aiMetallicFactor) == aiReturn_SUCCESS)
                {
                    material->metallic = aiMetallicFactor;
                }
                if (aiString aiRoughnessMetallicTexturePath{}; aiMaterial->GetTexture(AI_MATKEY_METALLIC_TEXTURE, &aiRoughnessMetallicTexturePath) == aiReturn_SUCCESS)
                {
                    const auto aiRoughnessMetallicImage = std::make_shared<Image>(baseDirectory / aiRoughnessMetallicTexturePath.C_Str());
                    const auto aiRoughnessMetallicTexture = textureBlueprint.build(aiRoughnessMetallicImage, 4u, false);
                    material->armMap = aiRoughnessMetallicTexture;
                }
                //if (aiString aiAmbientTexturePath{}; aiMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_LIGHTMAP, 0), aiAmbientTexturePath) == aiReturn_SUCCESS)
                //{
                //    const auto aiAmbientImage = std::make_shared<Image>(baseDirectory / aiAmbientTexturePath.C_Str());
                //    const auto aiAmbientTexture = textureBlueprint.build(aiAmbientImage, 4u, true);
                //    //material-> = aiRoughnessTexture;
                //    static_assert(false);
                //}
                //if (aiString aiEmissionTexturePath{}; aiMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_EMISSIVE, 0), aiEmissionTexturePath) == aiReturn_SUCCESS)
                //{
                //    const auto emissionImage = std::make_shared<Image>(baseDirectory / aiEmissionTexturePath.C_Str());
                //    const auto emissionTexture = textureBlueprint.build(emissionImage, 4u, true);
                //    material->emissionMap = emissionTexture;
                //}

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

                std::span<aiNode*> aiFrontNodeChildren{ aiFrontNode->mChildren, aiFrontNode->mNumChildren };
                const auto totalChildren = aiFrontNode->mNumMeshes == 1 ? 0 : aiFrontNodeChildren.size() + aiFrontNode->mNumMeshes;
                frontNode->children.reserve(totalChildren);

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
        static inline std::shared_ptr<Material> m_defaultMaterial{};
        static inline std::shared_ptr<VertexLayout> m_layout3f{};
        static inline std::shared_ptr<VertexLayout> m_layout2f{};
    };
}
