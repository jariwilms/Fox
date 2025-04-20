#pragma once

#include "Fox/Rendering/Buffer/VertexArray.hpp"

namespace fox::gfx
{
    struct Mesh
    {
    public:
        Mesh(std::shared_ptr<gfx::VertexArray> vertexArray)
            : vertexArray{ vertexArray } {}

        std::shared_ptr<gfx::VertexArray> vertexArray{};
    };
}
