#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Buffer/VertexArray.hpp"
#include "Helix/Rendering/Buffer/VertexBuffer.hpp"
#include "Helix/Rendering/Buffer/IndexBuffer.hpp"

namespace hlx
{
    struct Quad
    {
    public:
        Quad()
        {
            const auto layout3f = std::make_shared<VertexLayout>();
            layout3f->specify<float>(3);
            const auto layout2f = std::make_shared<VertexLayout>();
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

        const std::array<float, 12> positions =
        {
             1.0f, 1.0f,  0.0f,
            -1.0f, 1.0f,  0.0f,
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
        };
        const std::array<float, 12> normals =
        {
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
        };
        const std::array<float, 12> coordinates =
        {
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
        };
        const std::array<unsigned int, 6> indices =
        {
            0, 1, 2,
            0, 2, 3,
        };

        std::shared_ptr<VertexArray> vao{};
    };
}
