#pragma once

#include "stdafx.hpp"

#include "Quad.hpp"

namespace hlx
{
    struct Cube
    {
    public:
        Cube()
        {
            const auto layout3f = std::make_shared<VertexLayout>();
            const auto layout2f = std::make_shared<VertexLayout>();
            layout3f->specify<float>(3);
            layout2f->specify<float>(2);

            const auto positionsVBO = GraphicsAPI::create_vbo<float>(positions);
            const auto normalsVBO = GraphicsAPI::create_vbo<float>(normals);
            const auto coordinatesVBO = GraphicsAPI::create_vbo<float>(coordinates);
            const auto indicesIBO = GraphicsAPI::create_ibo(indices);

            vao = GraphicsAPI::create_vao();
            vao->tie(positionsVBO, layout3f);
            vao->tie(normalsVBO, layout3f);
            vao->tie(coordinatesVBO, layout2f);
            vao->tie(indicesIBO);
        }

        static inline const std::array<float, 72> positions
        {
             1.0f,  1.0f, -1.0f, 
             1.0f,  1.0f,  1.0f, 
             1.0f, -1.0f,  1.0f, 
             1.0f, -1.0f, -1.0f, 
                                 
            -1.0f,  1.0f, -1.0f, 
            -1.0f,  1.0f,  1.0f, 
            -1.0f, -1.0f,  1.0f, 
            -1.0f, -1.0f, -1.0f, 
                                 
             1.0f,  1.0f, -1.0f, 
            -1.0f,  1.0f, -1.0f, 
            -1.0f,  1.0f,  1.0f, 
             1.0f,  1.0f,  1.0f, 
                                 
             1.0f, -1.0f, -1.0f, 
            -1.0f, -1.0f, -1.0f, 
            -1.0f, -1.0f,  1.0f, 
             1.0f, -1.0f,  1.0f, 
                                 
             1.0f,  1.0f,  1.0f, 
            -1.0f,  1.0f,  1.0f, 
            -1.0f, -1.0f,  1.0f, 
             1.0f, -1.0f,  1.0f, 
                                 
             1.0f,  1.0f, -1.0f, 
            -1.0f,  1.0f, -1.0f, 
            -1.0f, -1.0f, -1.0f, 
             1.0f, -1.0f, -1.0f, 
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

        static inline std::shared_ptr<VertexArray> vao{};
    };
}
