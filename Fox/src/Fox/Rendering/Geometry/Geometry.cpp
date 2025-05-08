#include "stdafx.hpp"

#include "Geometry.hpp"
#include "Fox/IO/Import/Model/ModelImporter.hpp"

namespace fox::gfx
{
    void Geometry::Plane::init()
    {
        gfx::VertexLayout layout2f{};
        gfx::VertexLayout layout3f{};

        layout2f.specify<fox::float32_t>(2);
        layout3f.specify<fox::float32_t>(3);

        const auto& positionsVBO   = gfx::VertexBuffer<fox::float32_t>::create(positions);
        const auto& normalsVBO     = gfx::VertexBuffer<fox::float32_t>::create(normals);
        const auto& tangentsVBO    = gfx::VertexBuffer<fox::float32_t>::create(tangents);
        const auto& coordinatesVBO = gfx::VertexBuffer<fox::float32_t>::create(coordinates);
        const auto& indicesIBO     = gfx::IndexBuffer::create(indices);

        auto vertexArray = gfx::VertexArray::create();
        vertexArray->tie(positionsVBO,   layout3f);
        vertexArray->tie(normalsVBO,     layout3f);
        vertexArray->tie(tangentsVBO,    layout3f);
        vertexArray->tie(coordinatesVBO, layout2f);
        vertexArray->tie(indicesIBO);

        s_mesh = std::make_shared<gfx::Mesh>(vertexArray);
    }
    void Geometry::Cube::init()
    {
        gfx::VertexLayout layout2f{};
        gfx::VertexLayout layout3f{};

        layout2f.specify<fox::float32_t>(2);
        layout3f.specify<fox::float32_t>(3);

        const auto& positionsVBO   = gfx::VertexBuffer<fox::float32_t>::create(positions);
        const auto& normalsVBO     = gfx::VertexBuffer<fox::float32_t>::create(normals);
        const auto& tangentsVBO    = gfx::VertexBuffer<fox::float32_t>::create(tangents);
        const auto& coordinatesVBO = gfx::VertexBuffer<fox::float32_t>::create(coordinates);
        const auto& indicesIBO     = gfx::IndexBuffer::create(indices);

        auto vertexArray = VertexArray::create();
        vertexArray->tie(positionsVBO,   layout3f);
        vertexArray->tie(normalsVBO,     layout3f);
        vertexArray->tie(tangentsVBO,    layout3f);
        vertexArray->tie(coordinatesVBO, layout2f);
        vertexArray->tie(indicesIBO);

        s_mesh = std::make_shared<gfx::Mesh>(vertexArray);
    }
    void Geometry::Sphere::init()
    {
        const auto& model = io::ModelImporter::import("models/sphere/Sphere.gltf");
        s_mesh = model->meshes.at(0);
    }
}
