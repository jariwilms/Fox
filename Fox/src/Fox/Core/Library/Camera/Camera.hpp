#pragma once

#include "Fox/Core/Types.hpp"

#include "Fox/Rendering/Projection/Projection.hpp"

namespace fox
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(fox::float32_t aspectRatio, fox::float32_t fov)
            : m_aspectRatio{ aspectRatio }, m_fov{ fov }, m_projection{ gfx::Projection::perspective_p{ m_aspectRatio, m_fov, 0.1f, 1000.0f } } {}

              fox::float32_t   aspect_ratio () const
        {
            return m_aspectRatio;
        }
              fox::float32_t   field_of_view() const
        {
            return m_fov;
        }
        const gfx::Projection& projection   () const
        {
            return m_projection;
        }

    protected:
        fox::float32_t  m_aspectRatio{ 1.0f };
        fox::float32_t  m_fov        { 90.0f };
        gfx::Projection m_projection {};
        fox::Vector4f   m_clearColor { 0.0f, 0.0f, 0.0f, 1.0f };
    };
}
