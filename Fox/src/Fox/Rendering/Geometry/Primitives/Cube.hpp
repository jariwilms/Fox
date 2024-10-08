//#pragma once
//
//#include "stdafx.hpp"
//
//#include "Fox/Rendering/API/GraphicsAPI.hpp"
//#include "Fox/Rendering/Buffer/VertexArray.hpp"
//#include "Fox/Rendering/Buffer/VertexBuffer.hpp"
//#include "Fox/Rendering/Buffer/IndexBuffer.hpp"
//
//namespace fox
//{
//    struct Cube
//    {
//    public:
//        Cube()
//        {
//            const auto layout3f = std::make_shared<VertexLayout>();
//            const auto layout2f = std::make_shared<VertexLayout>();
//            layout3f->specify<float>(3);
//            layout2f->specify<float>(2);
//
//            const auto positionsVBO = GraphicsAPI::create_vbo<float>(positions);
//            const auto normalsVBO = GraphicsAPI::create_vbo<float>(normals);
//            const auto coordinatesVBO = GraphicsAPI::create_vbo<float>(coordinates);
//            const auto indicesIBO = GraphicsAPI::create_ibo(indices);
//
//            s_vao = GraphicsAPI::create_vao();
//            s_vao->tie(positionsVBO, layout3f);
//            s_vao->tie(normalsVBO, layout3f);
//            s_vao->tie(coordinatesVBO, layout2f);
//            s_vao->tie(indicesIBO);
//        }
//
//        static inline const std::array<float, 72> positions
//        {
//             1.0f,  1.0f, -1.0f,
//             1.0f,  1.0f,  1.0f,
//             1.0f, -1.0f,  1.0f,
//             1.0f, -1.0f, -1.0f,
//
//            -1.0f,  1.0f, -1.0f,
//            -1.0f,  1.0f,  1.0f,
//            -1.0f, -1.0f,  1.0f,
//            -1.0f, -1.0f, -1.0f,
//
//             1.0f,  1.0f, -1.0f,
//            -1.0f,  1.0f, -1.0f,
//            -1.0f,  1.0f,  1.0f,
//             1.0f,  1.0f,  1.0f,
//
//             1.0f, -1.0f, -1.0f,
//            -1.0f, -1.0f, -1.0f,
//            -1.0f, -1.0f,  1.0f,
//             1.0f, -1.0f,  1.0f,
//
//             1.0f,  1.0f,  1.0f,
//            -1.0f,  1.0f,  1.0f,
//            -1.0f, -1.0f,  1.0f,
//             1.0f, -1.0f,  1.0f,
//
//             1.0f,  1.0f, -1.0f,
//            -1.0f,  1.0f, -1.0f,
//            -1.0f, -1.0f, -1.0f,
//             1.0f, -1.0f, -1.0f,
//        };
//        static inline const std::array<float, 72> normals
//        {
//             1.0f,  0.0f,  0.0f,
//             1.0f,  0.0f,  0.0f,
//             1.0f,  0.0f,  0.0f,
//             1.0f,  0.0f,  0.0f,
//
//            -1.0f,  0.0f,  0.0f,
//            -1.0f,  0.0f,  0.0f,
//            -1.0f,  0.0f,  0.0f,
//            -1.0f,  0.0f,  0.0f,
//
//             0.0f,  1.0f,  0.0f,
//             0.0f,  1.0f,  0.0f,
//             0.0f,  1.0f,  0.0f,
//             0.0f,  1.0f,  0.0f,
//
//             0.0f, -1.0f,  0.0f,
//             0.0f, -1.0f,  0.0f,
//             0.0f, -1.0f,  0.0f,
//             0.0f, -1.0f,  0.0f,
//
//             0.0f,  0.0f,  1.0f,
//             0.0f,  0.0f,  1.0f,
//             0.0f,  0.0f,  1.0f,
//             0.0f,  0.0f,  1.0f,
//
//             0.0f,  0.0f, -1.0f,
//             0.0f,  0.0f, -1.0f,
//             0.0f,  0.0f, -1.0f,
//             0.0f,  0.0f, -1.0f,
//        };
//        static inline const std::array<float, 48> coordinates
//        {
//             1.0f, 1.0f,
//             0.0f, 1.0f,
//             0.0f, 0.0f,
//             1.0f, 0.0f,
//
//             1.0f, 1.0f,
//             0.0f, 1.0f,
//             0.0f, 0.0f,
//             1.0f, 0.0f,
//
//             1.0f, 1.0f,
//             0.0f, 1.0f,
//             0.0f, 0.0f,
//             1.0f, 0.0f,
//
//             1.0f, 1.0f,
//             0.0f, 1.0f,
//             0.0f, 0.0f,
//             1.0f, 0.0f,
//
//             1.0f, 1.0f,
//             0.0f, 1.0f,
//             0.0f, 0.0f,
//             1.0f, 0.0f,
//
//             1.0f, 1.0f,
//             0.0f, 1.0f,
//             0.0f, 0.0f,
//             1.0f, 0.0f,
//        };
//        static inline const std::array<unsigned int, 36> indices
//        {
//             0,  1,  2,
//             0,  2,  3,
//
//             4,  5,  6,
//             4,  6,  7,
//
//             8,  9, 10,
//             8, 10, 11,
//
//            12, 13, 14,
//            12, 14, 15,
//
//            16, 17, 18,
//            16, 18, 19,
//
//            20, 21, 22,
//            20, 22, 23,
//        };
//
//    private:
//        static inline std::shared_ptr<VertexArray> s_vao{};
//    };
//}