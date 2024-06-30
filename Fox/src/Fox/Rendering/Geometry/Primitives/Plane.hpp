//#pragma once
//
//#include "stdafx.hpp"
//
//#include "Fox/Rendering/API/GraphicsAPI.hpp"
//#include "Fox/Rendering/Buffer/VertexArray.hpp"
//#include "Fox/Rendering/Buffer/VertexBuffer.hpp"
//#include "Fox/Rendering/Buffer/IndexBuffer.hpp"
//
//namespace hlx
//{
//    struct Plane
//    {
//    public:
//        Plane()
//            : vao{ GraphicsAPI::create_vao() }
//        {
//            const auto layout3f = std::make_shared<VertexLayout>();
//            const auto layout2f = std::make_shared<VertexLayout>();
//            layout3f->specify<float>(3);
//            layout2f->specify<float>(2);
//
//            const auto positionsVBO   = GraphicsAPI::create_vbo<float>(positions);
//            const auto normalsVBO     = GraphicsAPI::create_vbo<float>(normals);
//            const auto coordinatesVBO = GraphicsAPI::create_vbo<float>(coordinates);
//            const auto indicesIBO     = GraphicsAPI::create_ibo(indices);
//
//            vao->tie(positionsVBO,   layout3f);
//            vao->tie(normalsVBO,     layout3f);
//            vao->tie(coordinatesVBO, layout2f);
//            vao->tie(indicesIBO);
//        }
//
//        const std::array<float, 12> positions
//        {
//             1.0f,  1.0f,  0.0f,
//            -1.0f,  1.0f,  0.0f,
//            -1.0f, -1.0f,  0.0f,
//             1.0f, -1.0f,  0.0f,
//        };
//        const std::array<float, 12> normals
//        {
//            0.0f, 0.0f, 1.0f,
//            0.0f, 0.0f, 1.0f,
//            0.0f, 0.0f, 1.0f,
//            0.0f, 0.0f, 1.0f,
//        };
//        const std::array<float, 12> coordinates
//        {
//            1.0f, 1.0f,
//            0.0f, 1.0f,
//            0.0f, 0.0f,
//            1.0f, 0.0f,
//        };
//        const std::array<unsigned int, 6> indices
//        {
//            0, 1, 2,
//            0, 2, 3,
//        };
//
//        const std::shared_ptr<VertexArray> vao{};
//    };
//}
