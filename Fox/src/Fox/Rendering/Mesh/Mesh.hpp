#pragma once

#include "Fox/Rendering/Material/Material.hpp"

namespace fox::gfx
{
    class Mesh
    {
    public:
        Mesh(const std::shared_ptr<gfx::VertexArray> vertexArray)
            : m_vertexArray{ vertexArray } {}

        const std::shared_ptr<gfx::VertexArray> vertex_array() const
        {
            return m_vertexArray;
        }

    private:
        std::shared_ptr<gfx::VertexArray> m_vertexArray{};
    };
}
