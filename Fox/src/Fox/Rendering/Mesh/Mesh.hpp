#pragma once

#include "Helix/Rendering/Rendering.hpp"
#include "Helix/Rendering/Material/Material.hpp"

namespace hlx::gfx
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
