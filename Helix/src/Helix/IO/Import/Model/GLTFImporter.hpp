#pragma once

#include "stdafx.hpp"

#include "tinygltf/tiny_gltf.h"

#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Rendering.hpp"
#include "Helix/Rendering/Mesh/Mesh.hpp"

namespace hlx
{
    class GLTFImporter
    {
    public:
        template<typename T>
        static std::vector<T> load_vertices(const tinygltf::Model& model, unsigned int meshIndex, const std::string& identifier)
        {
            if (model.meshes.size() > meshIndex) throw std::out_of_range{ "Mesh index out of range!" };

            std::vector<T> result{};
            bool attributeFound{};

            const auto& mesh = model.meshes[meshIndex];
            for (const auto& primitive : mesh.primitives)
            {
                for (const auto& attribute : primitive.attributes)
                {
                    if (attribute.first == identifier)
                    {
                        const auto accessorIndex = attribute.second;
                        const auto& accessor = model.accessors[accessorIndex];

                        const auto bufferViewIndex = accessor.bufferView;
                        const auto bufferViewOffset = accessor.byteOffset;
                        const auto& bufferView = model.bufferViews[bufferViewIndex];

                        const auto bufferIndex = bufferView.buffer;
                        const auto bufferOffset = bufferView.byteOffset;
                        const auto bufferLength = bufferView.byteLength;
                        const auto bufferStride = bufferView.byteStride;
                        const auto& buffer = model.buffers[bufferIndex];



                        const auto count = accessor.count;
                        const auto dataType = accessor.type;
                        const auto componentType = accessor.componentType;

                        const auto startOffset = bufferViewOffset + bufferOffset;

                        switch (dataType)
                        {
                            case (TINYGLTF_TYPE_VEC2): 
                            {
                                const auto ptr = reinterpret_cast<const glm::vec2*>(buffer.data.data() + startOffset);
                                const auto vec = std::vector<glm::vec2>{ ptr, ptr + count };

                                for (const auto& v : vec)
                                {
                                    auto asd = glm::vec3{ v.x, v.y, 0.0f };
                                    result.push_back(asd);
                                }

                                break;
                            }
                            case (TINYGLTF_TYPE_VEC3): 
                            {
                                const auto ptr = reinterpret_cast<const glm::vec3*>(buffer.data.data() + startOffset);
                                const auto vec = std::vector<glm::vec3>{ ptr, ptr + count };
                                result = std::vector<T>{ vec.begin(), vec.end() };

                                break;
                            }
                            case (TINYGLTF_TYPE_VEC4): 
                            {
                                const auto ptr = reinterpret_cast<const glm::vec4*>(buffer.data.data() + startOffset);
                                const auto vec = std::vector<glm::vec4>{ ptr, ptr + count };
                                result = std::vector<T>{ vec.begin(), vec.end() };

                                break;
                            }

                            default: throw std::invalid_argument{ "Invalid argument!" };
                        }

                        attributeFound = true;
                    }
                }

                if (!attributeFound) throw std::runtime_error{ "Given identifier does not exist!" };
            }

            return result;
        }
        static std::vector<unsigned int> load_indices(const tinygltf::Model& model)
        {
            std::vector<unsigned int> result{};



            const auto& accessor = model.accessors[3];

            const auto bufferViewIndex = accessor.bufferView;
            const auto bufferViewOffset = accessor.byteOffset;
            const auto& bufferView = model.bufferViews[bufferViewIndex];

            const auto bufferIndex = bufferView.buffer;
            const auto bufferOffset = bufferView.byteOffset;
            const auto bufferLength = bufferView.byteLength;
            const auto bufferStride = bufferView.byteStride;
            const auto& buffer = model.buffers[bufferIndex];



            const auto count = accessor.count;
            const auto dataType = accessor.type;
            const auto componentType = accessor.componentType;

            const auto startOffset = bufferViewOffset + bufferOffset;

            const auto ptr = reinterpret_cast<const unsigned short*>(buffer.data.data() + startOffset);
            const auto vec = std::vector<unsigned short>{ ptr, ptr + count };
            result = std::vector<unsigned int>{ vec.begin(), vec.end() };



            return result;
        }

        static auto import()
        {
            tinygltf::Model model;
            tinygltf::TinyGLTF loader;
            std::string err;
            std::string warn;

            bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, "assets/models/cube/cube.gltf");

            auto positions = load_vertices<glm::vec3>(model, 0, "POSITION");
            auto normals = load_vertices<glm::vec3>(model, 0, "NORMAL");
            auto texCoords = load_vertices<glm::vec2>(model, 0, "TEXCOORD_0");
            auto indices = load_indices(model);













            const auto positionBuffer = GraphicsAPI::create_vbo<glm::vec3>(positions);
            const auto normalBuffer   = GraphicsAPI::create_vbo<glm::vec3>(normals);
            const auto texCoordBuffer = GraphicsAPI::create_vbo<glm::vec2>(texCoords);
            const auto indexBufer     = GraphicsAPI::create_ibo(indices);

            auto layout2f = std::make_shared<VertexLayout>();
            layout2f->specify<float>(2);

            auto layout3f = std::make_shared<VertexLayout>();
            layout3f->specify<float>(3);

            auto vao = GraphicsAPI::create_vao();
            vao->tie(positionBuffer, layout3f);
            vao->tie(normalBuffer, layout3f);
            vao->tie(texCoordBuffer, layout2f);
            vao->tie(indexBufer);

            return vao;
        }
    };
}
