//#pragma once
//
//#include "stdafx.hpp"
//
//#include "Fox/Rendering/API/GraphicsAPI.hpp"
//#include "Fox/Rendering/Buffer/VertexArray.hpp"
//#include "Fox/Rendering/Buffer/VertexBuffer.hpp"
//#include "Fox/Rendering/Buffer/IndexBuffer.hpp"
//
//namespace fox::gfx
//{
//    struct Geometry
//    {
//    public:
//        static void init()
//        {
//            Plane::init();
//            Cube::init();
//        }
//
//        struct Plane
//        {
//        public:
//            friend Geometry;
//
//            static const std::shared_ptr<Mesh> mesh()
//            {
//                return s_mesh;
//            }
//
//            static inline const std::array<float, 12> positions
//            {
//                 1.0f,  1.0f,  0.0f,
//                -1.0f,  1.0f,  0.0f,
//                -1.0f, -1.0f,  0.0f,
//                 1.0f, -1.0f,  0.0f,
//            };
//            static inline const std::array<float, 12> normals
//            {
//                0.0f, 0.0f, 1.0f,
//                0.0f, 0.0f, 1.0f,
//                0.0f, 0.0f, 1.0f,
//                0.0f, 0.0f, 1.0f,
//            };
//            static inline const std::array<float, 12> coordinates
//            {
//                1.0f, 1.0f,
//                0.0f, 1.0f,
//                0.0f, 0.0f,
//                1.0f, 0.0f,
//            };
//            static inline const std::array<unsigned int, 6> indices
//            {
//                0, 1, 2,
//                0, 2, 3,
//            };
//
//        private:
//            static void init()
//            {
//                const auto layout3f = std::make_shared<VertexLayout>();
//                const auto layout2f = std::make_shared<VertexLayout>();
//                layout3f->specify<float>(3);
//                layout2f->specify<float>(2);
//
//                const auto positionsVBO   = GFX_DEPRECATED::create_vertex_buffer<float>(positions);
//                const auto normalsVBO     = GFX_DEPRECATED::create_vertex_buffer<float>(normals);
//                const auto coordinatesVBO = GFX_DEPRECATED::create_vertex_buffer<float>(coordinates);
//                const auto indicesIBO     = GFX_DEPRECATED::create_index_buffer(indices);
//
//                auto vertexArray = GFX_DEPRECATED::create_vertex_array();
//                vertexArray->tie(positionsVBO, layout3f);
//                vertexArray->tie(normalsVBO, layout3f);
//                vertexArray->tie(coordinatesVBO, layout2f);
//                vertexArray->tie(indicesIBO);
//
//                s_mesh = std::make_shared<Mesh>(vertexArray);
//            }
//
//            static inline std::shared_ptr<Mesh> s_mesh{};
//        };
//        struct Cube
//        {
//        public:
//            friend Geometry;
//
//            static const std::shared_ptr<Mesh> mesh()
//            {
//                return s_mesh;
//            }
//
//            static inline const std::array<float, 72> positions
//            {
//                 0.5f,  0.5f,  0.5f, 
//                -0.5f,  0.5f,  0.5f, 
//                -0.5f, -0.5f,  0.5f, 
//                 0.5f, -0.5f,  0.5f, 
//
//                -0.5f,  0.5f, -0.5f, 
//                 0.5f,  0.5f, -0.5f, 
//                 0.5f, -0.5f, -0.5f,
//                -0.5f, -0.5f, -0.5f,
//
//                -0.5f,  0.5f,  0.5f, 
//                -0.5f,  0.5f, -0.5f, 
//                -0.5f, -0.5f, -0.5f, 
//                -0.5f, -0.5f,  0.5f, 
//
//                 0.5f,  0.5f, -0.5f,
//                 0.5f,  0.5f,  0.5f,
//                 0.5f, -0.5f,  0.5f,
//                 0.5f, -0.5f, -0.5f,
//
//                 0.5f, -0.5f,  0.5f, 
//                -0.5f, -0.5f,  0.5f, 
//                -0.5f, -0.5f, -0.5f, 
//                 0.5f, -0.5f, -0.5f, 
//
//                 0.5f,  0.5f, -0.5f,
//                -0.5f,  0.5f, -0.5f,
//                -0.5f,  0.5f,  0.5f,
//                 0.5f,  0.5f,  0.5f,
//            };
//            static inline const std::array<float, 72> normals
//            {
//                 1.0f,  0.0f,  0.0f,
//                 1.0f,  0.0f,  0.0f,
//                 1.0f,  0.0f,  0.0f,
//                 1.0f,  0.0f,  0.0f,
//
//                -1.0f,  0.0f,  0.0f,
//                -1.0f,  0.0f,  0.0f,
//                -1.0f,  0.0f,  0.0f,
//                -1.0f,  0.0f,  0.0f,
//
//                 0.0f,  1.0f,  0.0f,
//                 0.0f,  1.0f,  0.0f,
//                 0.0f,  1.0f,  0.0f,
//                 0.0f,  1.0f,  0.0f,
//
//                 0.0f, -1.0f,  0.0f,
//                 0.0f, -1.0f,  0.0f,
//                 0.0f, -1.0f,  0.0f,
//                 0.0f, -1.0f,  0.0f,
//
//                 0.0f,  0.0f,  1.0f,
//                 0.0f,  0.0f,  1.0f,
//                 0.0f,  0.0f,  1.0f,
//                 0.0f,  0.0f,  1.0f,
//
//                 0.0f,  0.0f, -1.0f,
//                 0.0f,  0.0f, -1.0f,
//                 0.0f,  0.0f, -1.0f,
//                 0.0f,  0.0f, -1.0f,
//            };
//            static inline const std::array<float, 48> coordinates
//            {
//                 1.0f, 1.0f,
//                 0.0f, 1.0f,
//                 0.0f, 0.0f,
//                 1.0f, 0.0f,
//
//                 1.0f, 1.0f,
//                 0.0f, 1.0f,
//                 0.0f, 0.0f,
//                 1.0f, 0.0f,
//
//                 1.0f, 1.0f,
//                 0.0f, 1.0f,
//                 0.0f, 0.0f,
//                 1.0f, 0.0f,
//
//                 1.0f, 1.0f,
//                 0.0f, 1.0f,
//                 0.0f, 0.0f,
//                 1.0f, 0.0f,
//
//                 1.0f, 1.0f,
//                 0.0f, 1.0f,
//                 0.0f, 0.0f,
//                 1.0f, 0.0f,
//
//                 1.0f, 1.0f,
//                 0.0f, 1.0f,
//                 0.0f, 0.0f,
//                 1.0f, 0.0f,
//            };
//            static inline const std::array<unsigned int, 36> indices
//            {
//                 0,  1,  2,
//                 0,  2,  3,
//
//                 4,  5,  6,
//                 4,  6,  7,
//
//                 8,  9, 10,
//                 8, 10, 11,
//
//                12, 13, 14,
//                12, 14, 15,
//
//                16, 17, 18,
//                16, 18, 19,
//
//                20, 21, 22,
//                20, 22, 23,
//            };
//
//        private:
//            static void init()
//            {
//                const auto layout3f = std::make_shared<VertexLayout>();
//                const auto layout2f = std::make_shared<VertexLayout>();
//                layout3f->specify<float>(3);
//                layout2f->specify<float>(2);
//
//                const auto positionsVBO   = GFX_DEPRECATED::create_vertex_buffer<float>(positions);
//                const auto normalsVBO     = GFX_DEPRECATED::create_vertex_buffer<float>(normals);
//                const auto coordinatesVBO = GFX_DEPRECATED::create_vertex_buffer<float>(coordinates);
//                const auto indicesIBO     = GFX_DEPRECATED::create_index_buffer(indices);
//
//                auto vertexArray = GFX_DEPRECATED::create_vertex_array();
//                vertexArray->tie(positionsVBO, layout3f);
//                vertexArray->tie(normalsVBO, layout3f);
//                vertexArray->tie(coordinatesVBO, layout2f);
//                vertexArray->tie(indicesIBO);
//
//                s_mesh = std::make_shared<Mesh>(vertexArray);
//            }
//
//            static inline std::shared_ptr<Mesh> s_mesh{};
//        };
//    };
//}