#pragma once

#include "Fox/Rendering/Material/Material.hpp"

namespace fox::gfx
{
    struct Mesh
    {
    public:
        Mesh(std::shared_ptr<gfx::VertexArray> vertexArray)
            : vertexArray{ vertexArray } {}

        std::shared_ptr<gfx::VertexArray> vertexArray{};

        //std::shared_ptr<gfx::VertexBuffer<api::Buffer::Access::Static, float>> positions{};
        //std::shared_ptr<gfx::VertexBuffer<api::Buffer::Access::Static, float>> normals{};
        //std::shared_ptr<gfx::VertexBuffer<api::Buffer::Access::Static, float>> tangents{};
        //std::shared_ptr<gfx::VertexBuffer<api::Buffer::Access::Static, float>> textureCoordinates{};
        //std::shared_ptr<gfx::IndexBuffer<api::Buffer::Access::Static>>         indices{};
    };
}
