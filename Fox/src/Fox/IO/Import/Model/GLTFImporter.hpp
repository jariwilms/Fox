#pragma once

#include "stdafx.hpp"

#include "tinygltf/tiny_gltf.h"

#include "Fox/Rendering/Rendering.hpp"
#include "Fox/Rendering/Mesh/Mesh.hpp"
#include "Fox/Rendering/Model/Model.hpp"
#include "Fox/Core/Library/Image/Image.hpp"

namespace fox::io
{
    class GLTFImporter
    {
    public:
        static std::shared_ptr<gfx::Model> import2(const std::filesystem::path& path)
        {
            auto model = std::make_shared<fox::gfx::Model>();



            tinygltf::Model    gltfModel{};
            tinygltf::TinyGLTF gltfLoader{};
            tinygltf::Scene    gltfScene{};

            std::string        error{};
            std::string        warning{};

            const auto& isLoaded = gltfLoader.LoadASCIIFromFile(&gltfModel, &error, &warning, "assets/" + path.string());
            if (!isLoaded)
            {
                std::cout << error;

                throw std::runtime_error{ "Failed to load model!" };
            }
            if (!warning.empty())
            {
                std::cout << warning << '\n';
            }



            if (gltfModel.scenes.empty()) throw std::invalid_argument{ "Model requires at least one scene!" };
            if (gltfModel.defaultScene == -1)
            {
                gltfScene = gltfModel.scenes.at(0);

                std::cout << "Model has no default scene, loading scene 0.";
            }
            else
            {
                gltfScene = gltfModel.scenes.at(gltfModel.defaultScene);
            }



            if (gltfScene.nodes.empty()) throw std::invalid_argument{ "Scene requires at least one node!" };
            if (gltfScene.nodes.size() == 1) //The scene has a single root node
            {
                const auto& gRootNodeIndex = gltfScene.nodes.at(0);

                create_nodes(*model->root, gltfModel, gltfModel.nodes.at(gRootNodeIndex));
            }
            else                             //The scene has multiple root nodes => assign to single parent
            {
                tinygltf::Node gRootNode{};
                gRootNode.children = gltfScene.nodes;

                create_nodes(*model->root, gltfModel, gRootNode);
            }


            
            const auto& load_meshes = [](const tinygltf::Model& gModel) -> auto
                {
                    std::bitset<4> attributesFound{};

                    using access_t = fox::gfx::api::Buffer::Access;
                    using varr_t   = fox::gfx::VertexArray;
                    using vbuf2f_t = fox::gfx::VertexBuffer<access_t::Static, fox::Vector2f>;
                    using vbuf3f_t = fox::gfx::VertexBuffer<access_t::Static, fox::Vector3f>;
                    using ibuf_t   = fox::gfx::IndexBuffer<access_t::Static>;

                    const auto& layout2f = fox::gfx::VertexLayout<float>({ 2 });
                    const auto& layout3f = fox::gfx::VertexLayout<float>({ 3 });

                    std::shared_ptr<varr_t>   vertexArray{};
                    std::shared_ptr<vbuf3f_t> positionsBuffer{};
                    std::shared_ptr<vbuf3f_t> normalsBuffer{};
                    std::shared_ptr<vbuf2f_t> texCoordsBuffer{};
                    std::shared_ptr<vbuf3f_t> tangentsBuffer{};
                    std::shared_ptr<ibuf_t>   indicesBuffer{};



                    std::vector<std::shared_ptr<gfx::Mesh>> meshes{};

                    for (const auto& gltfMesh : gModel.meshes)
                    {
                        for (const auto& gltfPrimitive : gltfMesh.primitives)
                        {
                            vertexArray = std::make_shared<fox::gfx::VertexArray>();

                            for (const auto& gltfAttribute : gltfPrimitive.attributes)
                            {
                                if (gltfAttribute.first == "POSITION")
                                {
                                    auto positions = load_vertices<Vector3f>(gModel, 0, "POSITION");
                                    positionsBuffer = std::make_shared<vbuf3f_t>(positions);

                                    attributesFound.set(0, true);
                                }
                                if (gltfAttribute.first == "NORMAL")
                                {
                                    auto normals = load_vertices<Vector3f>(gModel, 0, "NORMAL");
                                    normalsBuffer = std::make_shared<vbuf3f_t>(normals);

                                    attributesFound.set(1, true);
                                }
                                if (gltfAttribute.first == "TANGENT")
                                {
                                    auto tangents = load_vertices<Vector3f>(gModel, 0, "TANGENT");
                                    tangentsBuffer = std::make_shared<vbuf3f_t>(tangents);

                                    attributesFound.set(2, true);
                                }
                                if (gltfAttribute.first == "TEXCOORD_0")
                                {
                                    auto texCoords = load_vertices<Vector2f>(gModel, 0, "TEXCOORD_0");
                                    texCoordsBuffer = std::make_shared<vbuf2f_t>(texCoords);

                                    attributesFound.set(3, true);
                                }
                            }

                            if (!attributesFound.all()) throw std::runtime_error{ "Mesh is missing one or multiple required data buffers!" };

                            auto indices = load_indices(gModel);
                            indicesBuffer = std::make_shared<ibuf_t>(indices);

                            vertexArray->tie(positionsBuffer, layout3f);
                            vertexArray->tie(normalsBuffer, layout3f);
                            vertexArray->tie(tangentsBuffer, layout3f);
                            vertexArray->tie(texCoordsBuffer, layout2f);
                            vertexArray->tie(indicesBuffer);
                        }

                        auto mesh = std::make_shared<fox::gfx::Mesh>(vertexArray);
                        meshes.emplace_back(std::move(mesh));
                    }

                    return meshes;
                };
            model->meshes = load_meshes(gltfModel);

            const auto& load_materials = [](const tinygltf::Model& gltfModel, const std::filesystem::path& cwd) -> auto
                {
                    std::vector<std::shared_ptr<gfx::Texture2D>> textures{};
                    std::vector<std::shared_ptr<gfx::Material>>  materials{};

                    for (const auto& gltfTexture : gltfModel.textures)
                    {
                        const auto& gltfTextureFileName = gltfModel.images.at(gltfTexture.source).uri;
                        const auto& gltfTextureFile     = io::load(cwd / gltfTextureFileName);
                        const auto& gltfImage           = Image::decode(Image::Layout::RGBA8, *gltfTextureFile->read());
                        auto        texture             = std::make_shared<gfx::Texture2D>(gfx::Texture2D::Format::RGBA8_UNORM, gltfImage.dimensions(), gltfImage.data());

                        textures.emplace_back(std::move(texture));
                    }

                    for (const auto& gltfMaterial : gltfModel.materials)
                    {
                        auto material = std::make_shared<gfx::Material>();

                        const auto& baseColorTextureIndex = gltfMaterial.pbrMetallicRoughness.baseColorTexture.index;
                        const auto& armTextureIndex       = gltfMaterial.pbrMetallicRoughness.metallicRoughnessTexture.index;
                        const auto& normalTextureIndex    = gltfMaterial.normalTexture.index;

                        if (baseColorTextureIndex > -1) material->albedo = textures.at(baseColorTextureIndex);
                        if (armTextureIndex       > -1) material->arm    = textures.at(armTextureIndex);
                        if (normalTextureIndex    > -1) material->normal = textures.at(normalTextureIndex);

                        material->roughnessFactor = static_cast<fox::float32_t>(gltfMaterial.pbrMetallicRoughness.roughnessFactor);
                        material->metallicFactor  = static_cast<fox::float32_t>(gltfMaterial.pbrMetallicRoughness.metallicFactor);

                        materials.emplace_back(std::move(material));
                    }

                    return materials;
                };
            model->materials = load_materials(gltfModel, path.parent_path());



            return model;
        }

    protected:
        template<typename T>
        static std::vector<T> load_vertices(const tinygltf::Model& model, unsigned int meshIndex, const std::string& identifier)
        {
            const auto find_attribute = [](const tinygltf::Primitive& primitive, const std::string& identifier) -> int
            {
                for (const auto& attribute : primitive.attributes)
                {
                    if (attribute.first == identifier) return attribute.second;
                }

                throw std::runtime_error{ "Requested identifier does not exist!" };
            };

            std::vector<T> result{};

            const auto& mesh = model.meshes[meshIndex];
            for (const auto& primitive : mesh.primitives)
            {
                const auto& accessorIndex    = find_attribute(primitive, identifier);
                const auto& accessor         = model.accessors[accessorIndex];

                const auto& bufferViewIndex  = accessor.bufferView;
                const auto& bufferViewOffset = accessor.byteOffset;
                const auto& bufferView       = model.bufferViews[bufferViewIndex];

                const auto& bufferIndex      = bufferView.buffer;
                const auto& bufferOffset     = bufferView.byteOffset;
                const auto& buffer           = model.buffers[bufferIndex];

                const auto& count            = accessor.count;
                const auto& dataType         = accessor.type;
                const auto& componentType    = accessor.componentType;
                                             
                const auto& startOffset      = bufferViewOffset + bufferOffset;

                switch (dataType)
                {
                    case (TINYGLTF_TYPE_VEC2): 
                    {
                        const auto& ptr = reinterpret_cast<const Vector2f*>(buffer.data.data() + startOffset);
                        const auto& vec = std::vector<Vector2f>{ ptr, ptr + count };

                        for (const auto& v : vec)
                        {
                            const auto& asd = Vector3f{ v.x, v.y, 0.0f };
                            result.emplace_back(asd);
                        }

                        break;
                    }
                    case (TINYGLTF_TYPE_VEC3): 
                    {
                        const auto& ptr = reinterpret_cast<const Vector3f*>(buffer.data.data() + startOffset);
                        const auto& vec = std::vector<Vector3f>{ ptr, ptr + count };
                        result = std::vector<T>{ vec.begin(), vec.end() };

                        break;
                    }
                    case (TINYGLTF_TYPE_VEC4): 
                    {
                        const auto& ptr = reinterpret_cast<const Vector4f*>(buffer.data.data() + startOffset);
                        const auto& vec = std::vector<Vector4f>{ ptr, ptr + count };
                        result = std::vector<T>{ vec.begin(), vec.end() };

                        break;
                    }

                    default: throw std::invalid_argument{ "Invalid argument!" };
                }
            }

            return result;
        }
        static std::vector<unsigned int> load_indices(const tinygltf::Model& model)
        {
            std::vector<unsigned int> result{};



            const auto& accessor         = model.accessors[0];

            const auto& bufferViewIndex  = accessor.bufferView;
            const auto& bufferViewOffset = accessor.byteOffset;
            const auto& bufferView       = model.bufferViews[bufferViewIndex];

            const auto& bufferIndex      = bufferView.buffer;
            const auto& bufferOffset     = bufferView.byteOffset;
            const auto& buffer           = model.buffers[bufferIndex];
            
            const auto& count            = accessor.count;
            const auto& dataType         = accessor.type;
            const auto& componentType    = accessor.componentType;

            const auto& startOffset      = bufferViewOffset + bufferOffset;



            const auto& ptr = reinterpret_cast<const unsigned short*>(buffer.data.data() + startOffset);
            const auto& vec = std::vector<unsigned short>{ ptr, ptr + count };
            result = std::vector<unsigned int>{ vec.begin(), vec.end() };



            return result;
        }
        static void create_nodes(gfx::Model::Node& mNode, const tinygltf::Model& gModel, const tinygltf::Node& gNode)
        {
            const auto& gMeshIndex        = gNode.mesh;
            const auto& gMesh             = gModel.meshes.at(gMeshIndex);
            const auto& gMaterialIndex    = gMesh.primitives.at(0).material;
            const auto& isMatrixTransform = gNode.matrix.size() == 16;

            if (gMeshIndex >     -1) mNode.meshIndex     = gMeshIndex;
            if (gMaterialIndex > -1) mNode.materialIndex = gMaterialIndex;
            if (isMatrixTransform)
            {
                mNode.localTransform = vector_to_matrix(gNode.matrix);
            }
            else
            {
                fox::Vector4f translation{};
                fox::Vector4f rotation{};
                fox::Vector4f scale{ 1.0f };

                if (!gNode.translation.empty())
                {
                    std::vector<fox::float32_t> tv{ gNode.translation.begin(), gNode.translation.end() };
                    translation = { tv.at(0), tv.at(1), tv.at(2), tv.at(3) };
                }
                if (!gNode.rotation.empty())
                {
                    std::vector<fox::float32_t> rv{ gNode.rotation.begin(), gNode.rotation.end() };
                    rotation = { rv.at(0), rv.at(1), rv.at(2), rv.at(3) };
                }
                if (!gNode.scale.empty())
                {
                    std::vector<fox::float32_t> sv{ gNode.scale.begin(), gNode.scale.end() };
                    scale = { sv.at(0), sv.at(1), sv.at(2), sv.at(3) };
                }

                fox::Transform transform{ translation, rotation, scale };
                mNode.localTransform = transform.matrix();
            }

            for (const auto& gChildIndex : gNode.children)
            {
                      auto& mChild = mNode.children.emplace_back(gfx::Model::Node{});
                const auto& gChild = gModel.nodes.at(gChildIndex);

                create_nodes(mChild, gModel, gChild);
            }
        };
        static fox::Matrix4f vector_to_matrix(const std::vector<fox::float64_t>& values)
        {
            std::vector<fox::float32_t> v{};
            std::transform(values.begin(), values.end(), std::back_inserter(v), [](fox::float64_t _) { return static_cast<fox::float32_t>(_); });

            fox::Matrix4f matrix{ v.at( 0), v.at( 1), v.at( 2), v.at( 3),
                                  v.at( 4), v.at( 5), v.at( 6), v.at( 7),
                                  v.at( 8), v.at( 9), v.at(10), v.at(11),
                                  v.at(12), v.at(13), v.at(14), v.at(15) }; //It be like that

            return matrix;
        };
        static void traverse_nodes(tinygltf::Node node, std::function<void(const tinygltf::Node&)> function)
        {
            function(node);

            for (const auto& child : node.children)
            {
                function(node);
            }
        }
        static int find_attribute_index(const tinygltf::Primitive& primitive, const std::string& identifier)
        {
            for (const auto& attribute : primitive.attributes)
            {
                if (attribute.first == identifier) return attribute.second;
            }

            throw std::runtime_error{ "Failed to find identifier!" };
        }
    };
}

