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
        enum class TextureType
        {
            Albedo, 
            Normal, 
            MetallicRoughness, 
            Specular, 
        };


        static void init()
        {
            m_defaultMaterial              = std::make_shared<Material>("Default");
            m_defaultMaterial->albedoMap   = GFX_DEPRECATED::create_texture(Texture::Format::RGBA8_SRGB, Texture::Filter::Trilinear, Texture::Wrapping::Repeat, Vector2u{ 1u, 1u }, Texture::Components::RGBA, utl::to_span(std::vector<byte>{ 0xFF, 0xFF, 0xFF, 0xFF }));
            m_defaultMaterial->normalMap   = GFX_DEPRECATED::create_texture(Texture::Format::RGB8_UNORM, Texture::Filter::Trilinear, Texture::Wrapping::Repeat, Vector2u{ 1u, 1u }, Texture::Components::RGB,  utl::to_span(std::vector<byte>{ 0x80, 0x80, 0xFF }));
            m_defaultMaterial->armMap      = GFX_DEPRECATED::create_texture(Texture::Format::RGB8_UNORM, Texture::Filter::Trilinear, Texture::Wrapping::Repeat, Vector2u{ 1u, 1u }, Texture::Components::RGB,  utl::to_span(std::vector<byte>{ 0x00, 0x80, 0x80 }));
            m_defaultMaterial->emissionMap = GFX_DEPRECATED::create_texture(Texture::Format::RGB8_UNORM, Texture::Filter::Trilinear, Texture::Wrapping::Repeat, Vector2u{ 1u, 1u }, Texture::Components::RGB,  utl::to_span(std::vector<byte>{ 0x00, 0x00, 0x00 }));

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
            const auto pFlags = 
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

            const auto* aiScene = importer.ReadFile(absolutePath.string(), pFlags);
            if (!aiScene || !aiScene->mRootNode || (aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)) throw std::runtime_error{"Failed to load model!"};

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

                const auto& meshVertexArray     = GFX_DEPRECATED::create_vertex_array();
                const auto& meshVertexBuffer    = GFX_DEPRECATED::create_vertex_buffer<Vector3f>(meshVertices); //TODO: vbo move impl
                const auto& meshNormalsBuffer   = GFX_DEPRECATED::create_vertex_buffer<Vector3f>(meshNormals);
                const auto& meshTexCoordsBuffer = GFX_DEPRECATED::create_vertex_buffer<Vector2f>(meshTexCoords);
                const auto& meshIndicesBuffer   = GFX_DEPRECATED::create_index_buffer(meshIndices);

                meshVertexArray->tie(meshVertexBuffer,    m_layout3f);
                meshVertexArray->tie(meshNormalsBuffer,   m_layout3f);
                meshVertexArray->tie(meshTexCoordsBuffer, m_layout2f);
                meshVertexArray->tie(meshIndicesBuffer);

                model->meshes.emplace_back(std::make_shared<Mesh>(meshVertexArray));
            }



            //Create instance of every material and add to model
            if (!aiScene->HasMaterials()) throw std::runtime_error{ "Model requires at least one material!" };

            std::span<aiMaterial*> aiMaterials{ aiScene->mMaterials, aiScene->mNumMaterials };
            for (const auto & aiMaterial : aiMaterials)
            {
                auto material = std::make_shared<Material>(*m_defaultMaterial);

                if (aiString aiMaterialName{}; aiMaterial->Get(AI_MATKEY_NAME, aiMaterialName) == aiReturn_SUCCESS && aiMaterialName.length > 0) material->name = aiMaterialName.C_Str();
                else material->name = "Default";

                if (aiColor3D aiBaseColor{};       aiMaterial->Get(AI_MATKEY_BASE_COLOR, aiBaseColor)                   == aiReturn_SUCCESS)
                {
                    material->color = Vector4f{ aiBaseColor.r, aiBaseColor.g, aiBaseColor.b, 1.0f };
                }
                if (aiString  aiTexturePath{};     aiMaterial->GetTexture(AI_MATKEY_BASE_COLOR_TEXTURE, &aiTexturePath) == aiReturn_SUCCESS)
                {
                    const auto& image = _load_img(aiScene, baseDirectory, aiTexturePath, 4u);
                    material->albedoMap = GFX_DEPRECATED::create_texture(Texture::Format::RGBA8_SRGB, Texture::Filter::Trilinear, Texture::Wrapping::Repeat, image.dimensions(), Texture::Components::RGBA, image.data());
                }
                if (aiString  aiTexturePath{};     aiMaterial->GetTexture(aiTextureType_NORMALS, 0, &aiTexturePath)     == aiReturn_SUCCESS)
                {
                    const auto& image = _load_img(aiScene, baseDirectory, aiTexturePath, 3u);
                    material->normalMap = GFX_DEPRECATED::create_texture(Texture::Format::RGB8_UNORM, Texture::Filter::Trilinear, Texture::Wrapping::Repeat, image.dimensions(), Texture::Components::RGB, image.data());
                }
                if (ai_real   aiRoughnessFactor{}; aiMaterial->Get(AI_MATKEY_ROUGHNESS_FACTOR, aiRoughnessFactor)       == aiReturn_SUCCESS)
                {
                    material->roughness = aiRoughnessFactor;
                }
                if (ai_real   aiMetallicFactor{};  aiMaterial->Get(AI_MATKEY_METALLIC_FACTOR, aiMetallicFactor)         == aiReturn_SUCCESS)
                {
                    material->metallic = aiMetallicFactor;
                }
                if (aiString  aiTexturePath{};     aiMaterial->GetTexture(AI_MATKEY_METALLIC_TEXTURE, &aiTexturePath)   == aiReturn_SUCCESS)
                {
                    const auto& image = _load_img(aiScene, baseDirectory, aiTexturePath, 3u);
                    material->armMap = GFX_DEPRECATED::create_texture(Texture::Format::RGB8_UNORM, Texture::Filter::Trilinear, Texture::Wrapping::Repeat, image.dimensions(), Texture::Components::RGB, image.data());
                }
                
                //if (aiString aiTexturePath{}; aiMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_LIGHTMAP, 0), aiTexturePath) == aiReturn_SUCCESS)
                //{
                //    const auto aiAmbientImage = std::make_shared<Image>(baseDirectory / aiTexturePath.C_Str());
                //    const auto aiAmbientTexture = textureBlueprint.build(aiAmbientImage, 4u, true);
                //    //material-> = aiRoughnessTexture;
                //    static_assert(false);
                //}
                //if (aiString aiTexturePath{}; aiMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_EMISSIVE, 0), aiTexturePath) == aiReturn_SUCCESS)
                //{
                //    const auto emissionImage = std::make_shared<Image>(baseDirectory / aiTexturePath.C_Str());
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
                const auto& totalChildren = aiFrontNode->mNumMeshes == 1 ? 0 : aiFrontNodeChildren.size() + aiFrontNode->mNumMeshes;
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
        void _load_prop()
        {

        }
        static Image _load_img(const aiScene* aiScene, const std::filesystem::path& baseDirectory, const aiString& aiTexturePath, unsigned int channels)
        {
            const std::string texturePath{ aiTexturePath.C_Str() };
            if (texturePath.at(0) == '*')
            {
                const auto& aiTextureIndex = std::stoi(texturePath.substr(1));
                const auto& aiTexture = aiScene->mTextures[aiTextureIndex];
                const auto& aiSize = aiTexture->mWidth * std::max(aiTexture->mHeight, 1u);
                const auto& aiPtr = reinterpret_cast<byte*>(aiTexture->pcData);

                return Image::decode(std::vector<byte>{ aiPtr, aiPtr + aiSize }, channels);
            }
            else
            {
                auto file = IO::load<File>(baseDirectory / texturePath);
                return Image::decode(*file->read(), channels);
            }
        }

        static inline std::shared_ptr<Material> m_defaultMaterial{};
        static inline std::shared_ptr<VertexLayout> m_layout3f{};
        static inline std::shared_ptr<VertexLayout> m_layout2f{};
    };
}
