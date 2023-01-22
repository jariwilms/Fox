#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Component.hpp"
#include "Helix/Rendering/Projection/Projection.hpp"

namespace hlx
{
    class Camera : public Component
    {
    public:
        Camera()
        {
            m_fov = 90.0f;
            m_aspect = 16.0f / 9.0f;
            
            m_view = glm::lookAt(glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec3{ 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });
            m_projection = Projection::create<Projection::Type::Perspective>(m_fov, m_aspect, 0.001f, 10000.0f);
        }

        const glm::mat4& view() const
        {
            return m_view;
        }
        const glm::mat4& projection() const
        {
            return m_projection;
        }
        const glm::mat4& view_projection() const
        {
            return m_view * m_projection;
        }

        float aspect() const
        {
            return m_aspect;
        }
        
    protected:
        glm::mat4 m_view{};
        glm::mat4 m_projection{};
        float m_fov{};
        float m_aspect{};

        glm::vec4 m_backgroundColor{ 0.0f, 0.0f, 0.0f, 1.0f };
    };
}
