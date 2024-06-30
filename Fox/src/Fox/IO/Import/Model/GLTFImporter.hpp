//#pragma once
//
//#include "stdafx.hpp"
//
////#include "tinygltf/tiny_gltf.h"
//
//#include "Fox/Rendering/API/GraphicsAPI.hpp"
//#include "Fox/Rendering/Rendering.hpp"
//#include "Fox/Rendering/Mesh/Mesh.hpp"
//#include "Fox/Rendering/Model/Model.hpp"
//
//namespace hlx
//{
//    class GLTFImporter
//    {
//    public:
//        template<typename T>
//        static std::vector<T> load_vertices(const tinygltf::Model& model, unsigned int meshIndex, const std::string& identifier)
//        {
//            if (model.meshes.size() > meshIndex) throw std::out_of_range{ "Mesh index out of range!" };
//            const auto find_attribute = [](const tinygltf::Primitive& primitive, const std::string& identifier) -> int
//            {
//                for (const auto& attribute : primitive.attributes)
//                {
//                    if (attribute.first == identifier) return attribute.second;
//                }
//
//                throw std::runtime_error{ "Requested identifier does not exist!" };
//            };
//
//            std::vector<T> result{};
//
//            const auto& mesh = model.meshes[meshIndex];
//            for (const auto& primitive : mesh.primitives)
//            {
//                const auto accessorIndex = find_attribute(primitive, identifier);
//                const auto& accessor = model.accessors[accessorIndex];
//
//                const auto bufferViewIndex = accessor.bufferView;
//                const auto bufferViewOffset = accessor.byteOffset;
//                const auto& bufferView = model.bufferViews[bufferViewIndex];
//
//                const auto bufferIndex = bufferView.buffer;
//                const auto bufferOffset = bufferView.byteOffset;
//                const auto bufferLength = bufferView.byteLength;
//                const auto bufferStride = bufferView.byteStride;
//                const auto& buffer = model.buffers[bufferIndex];
//
//
//
//                const auto count = accessor.count;
//                const auto dataType = accessor.type;
//                const auto componentType = accessor.componentType;
//
//                const auto startOffset = bufferViewOffset + bufferOffset;
//
//                switch (dataType)
//                {
//                    case (TINYGLTF_TYPE_VEC2): 
//                    {
//                        const auto ptr = reinterpret_cast<const Vector2f*>(buffer.data.data() + startOffset);
//                        const auto vec = std::vector<Vector2f>{ ptr, ptr + count };
//
//                        for (const auto& v : vec)
//                        {
//                            auto asd = Vector3f{ v.x, v.y, 0.0f };
//                            result.push_back(asd);
//                        }
//
//                        break;
//                    }
//                    case (TINYGLTF_TYPE_VEC3): 
//                    {
//                        const auto ptr = reinterpret_cast<const Vector3f*>(buffer.data.data() + startOffset);
//                        const auto vec = std::vector<Vector3f>{ ptr, ptr + count };
//                        result = std::vector<T>{ vec.begin(), vec.end() };
//
//                        break;
//                    }
//                    case (TINYGLTF_TYPE_VEC4): 
//                    {
//                        const auto ptr = reinterpret_cast<const Vector4f*>(buffer.data.data() + startOffset);
//                        const auto vec = std::vector<Vector4f>{ ptr, ptr + count };
//                        result = std::vector<T>{ vec.begin(), vec.end() };
//
//                        break;
//                    }
//
//                    default: throw std::invalid_argument{ "Invalid argument!" };
//                }
//            }
//
//            return result;
//        }
//        static std::vector<unsigned int> load_indices(const tinygltf::Model& model)
//        {
//            std::vector<unsigned int> result{};
//
//
//
//            const auto& accessor = model.accessors[3];
//
//            const auto bufferViewIndex = accessor.bufferView;
//            const auto bufferViewOffset = accessor.byteOffset;
//            const auto& bufferView = model.bufferViews[bufferViewIndex];
//
//            const auto bufferIndex = bufferView.buffer;
//            const auto bufferOffset = bufferView.byteOffset;
//            const auto bufferLength = bufferView.byteLength;
//            const auto bufferStride = bufferView.byteStride;
//            const auto& buffer = model.buffers[bufferIndex];
//
//
//
//            const auto count = accessor.count;
//            const auto dataType = accessor.type;
//            const auto componentType = accessor.componentType;
//
//            const auto startOffset = bufferViewOffset + bufferOffset;
//
//            const auto ptr = reinterpret_cast<const unsigned short*>(buffer.data.data() + startOffset);
//            const auto vec = std::vector<unsigned short>{ ptr, ptr + count };
//            result = std::vector<unsigned int>{ vec.begin(), vec.end() };
//
//
//
//            return result;
//        }
//
//        static std::shared_ptr<Model> import(const std::filesystem::path& path = "")
//        {
//            auto model = std::make_shared<Model>();
//
//
//            tinygltf::Model gltfModel;
//            tinygltf::TinyGLTF gltfLoader;
//            std::string err;
//            std::string warn;
//
//            bool success = gltfLoader.LoadASCIIFromFile(&gltfModel, &err, &warn, "assets/models/cube/cube.gltf");
//            if (!success) throw std::runtime_error{ "Failed to load model!" };
//
//            auto positions = load_vertices<Vector3f>(gltfModel, 0, "POSITION");
//            auto normals = load_vertices<Vector3f>(gltfModel, 0, "NORMAL");
//            auto texCoords = load_vertices<Vector2f>(gltfModel, 0, "TEXCOORD_0");
//            auto indices = load_indices(gltfModel);
//
//
//
//            const auto positionBuffer = GraphicsAPI::create_vbo<Vector3f>(positions);
//            const auto normalBuffer   = GraphicsAPI::create_vbo<Vector3f>(normals);
//            const auto texCoordBuffer = GraphicsAPI::create_vbo<Vector2f>(texCoords);
//            const auto indexBufer     = GraphicsAPI::create_ibo(indices);
//
//            auto layout2f = std::make_shared<VertexLayout>();
//            layout2f->specify<float>(2);
//
//            auto layout3f = std::make_shared<VertexLayout>();
//            layout3f->specify<float>(3);
//
//            auto vao = GraphicsAPI::create_vao();
//            vao->tie(positionBuffer, layout3f);
//            vao->tie(normalBuffer, layout3f);
//            vao->tie(texCoordBuffer, layout2f);
//            vao->tie(indexBufer);
//        }
//    };
//}
