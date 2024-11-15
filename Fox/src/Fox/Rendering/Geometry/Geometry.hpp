#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/Rendering.hpp"
#include "Fox/Rendering/Mesh/Mesh.hpp"

namespace fox::gfx
{
    struct Geometry
    {
    public:
        static void init()
        {
            Plane::init();
            Cube::init();
        }

        struct Plane
        {
        public:
            friend Geometry;

            static const std::shared_ptr<Mesh> mesh()
            {
                return s_mesh;
            }

            static inline const std::array<float, 12> positions
            {
                 1.0f,  1.0f,  0.0f,
                -1.0f,  1.0f,  0.0f,
                -1.0f, -1.0f,  0.0f,
                 1.0f, -1.0f,  0.0f,
            };
            static inline const std::array<float, 12> normals
            {
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
            };
            static inline const std::array<float, 12> coordinates
            {
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f,
            };
            static inline const std::array<unsigned int, 6> indices
            {
                0, 1, 2,
                0, 2, 3,
            };

        private:
            static void init()
            {
                const auto& layout3f = VertexLayout<float, float, float>{};
                const auto& layout2f = VertexLayout<float, float>{};


                const auto& positionsVBO   = std::make_shared<VertexBuffer<Buffer::Access::Static, float>>(positions);
                const auto& normalsVBO     = std::make_shared<VertexBuffer<Buffer::Access::Static, float>>(positions);
                const auto& coordinatesVBO = std::make_shared<VertexBuffer<Buffer::Access::Static, float>>(positions);
                const auto& indicesIBO     = std::make_shared<IndexBuffer<Buffer::Access::Static>>(indices);

                auto vertexArray = std::make_shared<VertexArray>();
                vertexArray->tie(positionsVBO,   layout3f);
                vertexArray->tie(normalsVBO,     layout3f);
                vertexArray->tie(coordinatesVBO, layout2f);
                vertexArray->tie(indicesIBO);

                s_mesh = std::make_shared<Mesh>(vertexArray);
            }

            static inline std::shared_ptr<Mesh> s_mesh{};
        };
        struct Cube
        {
        public:
            friend Geometry;

            static const std::shared_ptr<Mesh> mesh()
            {
                return s_mesh;
            }

            static inline const std::array<float, 72> positions
            {
                 0.5f,  0.5f,  0.5f, 
                -0.5f,  0.5f,  0.5f, 
                -0.5f, -0.5f,  0.5f, 
                 0.5f, -0.5f,  0.5f, 

                -0.5f,  0.5f, -0.5f, 
                 0.5f,  0.5f, -0.5f, 
                 0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,

                -0.5f,  0.5f,  0.5f, 
                -0.5f,  0.5f, -0.5f, 
                -0.5f, -0.5f, -0.5f, 
                -0.5f, -0.5f,  0.5f, 

                 0.5f,  0.5f, -0.5f,
                 0.5f,  0.5f,  0.5f,
                 0.5f, -0.5f,  0.5f,
                 0.5f, -0.5f, -0.5f,

                 0.5f, -0.5f,  0.5f, 
                -0.5f, -0.5f,  0.5f, 
                -0.5f, -0.5f, -0.5f, 
                 0.5f, -0.5f, -0.5f, 

                 0.5f,  0.5f, -0.5f,
                -0.5f,  0.5f, -0.5f,
                -0.5f,  0.5f,  0.5f,
                 0.5f,  0.5f,  0.5f,
            };
            static inline const std::array<float, 72> normals
            {
                 1.0f,  0.0f,  0.0f,
                 1.0f,  0.0f,  0.0f,
                 1.0f,  0.0f,  0.0f,
                 1.0f,  0.0f,  0.0f,

                -1.0f,  0.0f,  0.0f,
                -1.0f,  0.0f,  0.0f,
                -1.0f,  0.0f,  0.0f,
                -1.0f,  0.0f,  0.0f,

                 0.0f,  1.0f,  0.0f,
                 0.0f,  1.0f,  0.0f,
                 0.0f,  1.0f,  0.0f,
                 0.0f,  1.0f,  0.0f,

                 0.0f, -1.0f,  0.0f,
                 0.0f, -1.0f,  0.0f,
                 0.0f, -1.0f,  0.0f,
                 0.0f, -1.0f,  0.0f,

                 0.0f,  0.0f,  1.0f,
                 0.0f,  0.0f,  1.0f,
                 0.0f,  0.0f,  1.0f,
                 0.0f,  0.0f,  1.0f,

                 0.0f,  0.0f, -1.0f,
                 0.0f,  0.0f, -1.0f,
                 0.0f,  0.0f, -1.0f,
                 0.0f,  0.0f, -1.0f,
            };
            static inline const std::array<float, 48> coordinates
            {
                 1.0f, 1.0f,
                 0.0f, 1.0f,
                 0.0f, 0.0f,
                 1.0f, 0.0f,

                 1.0f, 1.0f,
                 0.0f, 1.0f,
                 0.0f, 0.0f,
                 1.0f, 0.0f,

                 1.0f, 1.0f,
                 0.0f, 1.0f,
                 0.0f, 0.0f,
                 1.0f, 0.0f,

                 1.0f, 1.0f,
                 0.0f, 1.0f,
                 0.0f, 0.0f,
                 1.0f, 0.0f,

                 1.0f, 1.0f,
                 0.0f, 1.0f,
                 0.0f, 0.0f,
                 1.0f, 0.0f,

                 1.0f, 1.0f,
                 0.0f, 1.0f,
                 0.0f, 0.0f,
                 1.0f, 0.0f,
            };
            static inline const std::array<unsigned int, 36> indices
            {
                 0,  1,  2,
                 0,  2,  3,

                 4,  5,  6,
                 4,  6,  7,

                 8,  9, 10,
                 8, 10, 11,

                12, 13, 14,
                12, 14, 15,

                16, 17, 18,
                16, 18, 19,

                20, 21, 22,
                20, 22, 23,
            };

        private:
            static void init()
            {
                const auto layout3f = VertexLayout<float, float, float>{};
                const auto layout2f = VertexLayout<float, float>{};

                const auto& positionsVBO   = std::make_shared<VertexBuffer<Buffer::Access::Static, float>>(positions);
                const auto& normalsVBO     = std::make_shared<VertexBuffer<Buffer::Access::Static, float>>(positions);
                const auto& coordinatesVBO = std::make_shared<VertexBuffer<Buffer::Access::Static, float>>(positions);
                const auto& indicesIBO     = std::make_shared<IndexBuffer<Buffer::Access::Static>>(indices);

                auto vertexArray = std::make_shared<VertexArray>();
                vertexArray->tie(positionsVBO, layout3f);
                vertexArray->tie(normalsVBO, layout3f);
                vertexArray->tie(coordinatesVBO, layout2f);
                vertexArray->tie(indicesIBO);

                s_mesh = std::make_shared<Mesh>(vertexArray);
            }

            static inline std::shared_ptr<Mesh> s_mesh{};
        };
    };
}