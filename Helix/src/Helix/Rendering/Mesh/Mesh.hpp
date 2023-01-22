#pragma once

#include "Helix/Rendering/Rendering.hpp"

namespace hlx
{
    class Mesh
    {
    public:
        Mesh(const std::shared_ptr<VertexArray> vertexArray, const std::shared_ptr<VertexBuffer<glm::vec3>> positions, const std::shared_ptr<VertexBuffer<glm::vec3>> normals, const std::shared_ptr<VertexBuffer<glm::vec3>> texCoords)
            : m_vertexArray{ vertexArray }, m_positions{ positions }, m_normals{ normals }, m_texCoords{ texCoords } {}

    protected:
        const std::shared_ptr<VertexArray> m_vertexArray{};
        const std::shared_ptr<VertexBuffer<glm::vec3>> m_positions{};
        const std::shared_ptr<VertexBuffer<glm::vec3>> m_normals{};
        const std::shared_ptr<VertexBuffer<glm::vec3>> m_texCoords{};
    };
}
