#pragma once

#include "Fox/Rendering/Rendering.hpp"
#include "Fox/Rendering/Material/Material.hpp"

namespace fox::gfx
{
    class Mesh
    {
    public:
        Mesh(const std::shared_ptr<VertexArray> vertexArray)
            : m_vertexArray{ vertexArray } {}

        const std::shared_ptr<VertexArray> vertex_array() const
        {
            return m_vertexArray;
        }

    private:
        std::shared_ptr<VertexArray> m_vertexArray{};
    };
}
