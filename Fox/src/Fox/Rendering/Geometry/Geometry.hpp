#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/Mesh/Mesh.hpp"
#include "Fox/IO/Import/Model/ModelImporter.hpp"

namespace fox::gfx
{
    struct Geometry
    {
    public:
        static void init()
        {
            Plane::init();
            Cube::init();
            Sphere::init();
        }

        struct Plane
        {
        public:
            friend Geometry;

            static const std::shared_ptr<gfx::Mesh> mesh()
            {
                return s_mesh;
            }

            static inline const std::array<fox::float32_t, 12> positions
            {
                 1.0f,  1.0f,  0.0f,
                -1.0f,  1.0f,  0.0f,
                -1.0f, -1.0f,  0.0f,
                 1.0f, -1.0f,  0.0f,
            };
            static inline const std::array<fox::float32_t, 12> normals
            {
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
            };
            static inline const std::array<fox::float32_t, 8>  coordinates
            {
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f,
            };
            static inline const std::array<fox::uint32_t, 6>   indices
            {
                0, 1, 2,
                0, 2, 3,
            };

        private:
            static void init()
            {
                const auto& layout3f = gfx::VertexLayout<fox::float32_t>{ 3 };
                const auto& layout2f = gfx::VertexLayout<fox::float32_t>{ 2 };

                s_positions   = std::make_shared<gfx::VertexBuffer<Buffer::Access::Static, fox::float32_t>>(positions);
                s_normals     = std::make_shared<gfx::VertexBuffer<Buffer::Access::Static, fox::float32_t>>(normals);
                s_coordinates = std::make_shared<gfx::VertexBuffer<Buffer::Access::Static, fox::float32_t>>(coordinates);
                s_indices     = std::make_shared<gfx::IndexBuffer<Buffer::Access::Static>>(indices);

                auto vertexArray = std::make_shared<gfx::VertexArray>();
                vertexArray->tie(s_positions,   layout3f);
                vertexArray->tie(s_normals,     layout3f);
                vertexArray->tie(s_coordinates, layout2f);
                vertexArray->tie(s_indices);

                s_mesh = std::make_shared<gfx::Mesh>(vertexArray);
            }

            static inline std::shared_ptr<gfx::Mesh> s_mesh{};
            static inline std::shared_ptr<gfx::VertexBuffer<gfx::Buffer::Access::Static, fox::float32_t>> s_positions{};
            static inline std::shared_ptr<gfx::VertexBuffer<gfx::Buffer::Access::Static, fox::float32_t>> s_normals{};
            static inline std::shared_ptr<gfx::VertexBuffer<gfx::Buffer::Access::Static, fox::float32_t>> s_coordinates{};
            static inline std::shared_ptr<gfx::IndexBuffer<gfx::Buffer::Access::Static>> s_indices{};
        };
        struct Cube
        {
        public:
            friend Geometry;

            static const std::shared_ptr<gfx::Mesh> mesh()
            {
                return s_mesh;
            }

            static inline const std::array<fox::float32_t, 72> positions
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
            static inline const std::array<fox::float32_t, 72> normals
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
            static inline const std::array<fox::float32_t, 48> coordinates
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
            static inline const std::array<fox::uint32_t, 36> indices
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
                const auto layout3f = VertexLayout<fox::float32_t>{ 3 };
                const auto layout2f = VertexLayout<fox::float32_t>{ 2 };

                const auto& positionsVBO   = std::make_shared<VertexBuffer<Buffer::Access::Static, fox::float32_t>>(positions);
                const auto& normalsVBO     = std::make_shared<VertexBuffer<Buffer::Access::Static, fox::float32_t>>(positions);
                const auto& coordinatesVBO = std::make_shared<VertexBuffer<Buffer::Access::Static, fox::float32_t>>(positions);
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
        struct Sphere
        {
            friend Geometry;

            static const std::shared_ptr<gfx::Mesh> mesh()
            {
                return s_mesh;
            }

        private:
            static void init()
            {
                const auto& model = io::ModelImporter::import2("models/sphere/Sphere.gltf");
                s_mesh = model->meshes.at(0);
            }

            static inline std::shared_ptr<gfx::Mesh> s_mesh{};
        };
    };
}