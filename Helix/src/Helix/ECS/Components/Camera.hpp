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
            m_fov = 60.0f;                                                     //
            m_aspect = 16.0f / 9.0f;                                           //TODO: fetch aspect from window?
            
            m_projection = Projection::create<Projection::Type::Perspective>(m_fov, m_aspect, 0.001f, 10000.0f);
        }

        float fov() const
        {
            return m_fov;
        }
        float aspect() const
        {
            return m_aspect;
        }
        const glm::mat4& projection() const
        {
            return m_projection;
        }
        
    protected:
        float m_fov{};
        float m_aspect{};

        glm::mat4 m_projection{};

        glm::vec4 m_backgroundColor{ 0.0f, 0.0f, 0.0f, 1.0f };
    };
}
