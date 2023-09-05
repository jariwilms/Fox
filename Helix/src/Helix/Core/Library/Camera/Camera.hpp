#pragma once

#include "Helix/Rendering/Projection/Projection.hpp"

namespace hlx
{
    class Camera
    {
    public:
        Camera()
        {
            m_fov = 60.0f;
            m_aspect = 16.0f / 9.0f;                                           //TODO: pass window perspective into ctor / get perspective from config?

            m_projection = Projection::create<Projection::Type::Perspective>(m_fov, m_aspect, 0.01f, 10000.0f);
        }
        virtual ~Camera() = default;

        float field_of_view() const
        {
            return m_fov;
        }
        float aspect_ratio() const
        {
            return m_aspect;
        }
        const Matrix4f& projection_matrix() const
        {
            return m_projection;
        }

    protected:
        float m_fov{};
        float m_aspect{};

        Matrix4f m_projection{};

        Vector4f m_clearColor{ 0.0f, 0.0f, 0.0f, 1.0f };
    };
}
