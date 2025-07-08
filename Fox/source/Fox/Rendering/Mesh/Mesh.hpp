#pragma once

#include <fox/rendering/buffer/vertex_array.hpp>

namespace fox::gfx
{
    struct Mesh
    {
    public:
        Mesh(std::shared_ptr<const gfx::VertexArray> vertexArray)
            : vertexArray{ vertexArray } {}

        std::shared_ptr<const gfx::VertexArray> vertexArray;
    };
}
