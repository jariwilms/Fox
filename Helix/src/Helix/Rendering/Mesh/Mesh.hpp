#pragma once

#include "Helix/Rendering/Rendering.hpp"
#include "Helix/Rendering/Material/Material.hpp"

namespace hlx
{
    class Mesh
    {
    public:
        Mesh(const std::shared_ptr<VertexArray> vertexArray, const std::shared_ptr<DefaultMaterial> material)
            : m_vertexArray{ vertexArray }, m_material{ material } {}

        const std::shared_ptr<VertexArray> vao() const
        {
            return m_vertexArray;
        }
        const std::shared_ptr<DefaultMaterial> material() const
        {
            return m_material;
        }

    private:
        const std::shared_ptr<VertexArray> m_vertexArray{};
        const std::shared_ptr<DefaultMaterial> m_material{};
    };
}
