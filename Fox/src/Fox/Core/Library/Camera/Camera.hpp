#pragma once

#include "Fox/Core/Types.hpp"

#include "Fox/Rendering/Projection/Projection.hpp"

namespace fox
{
    class Camera
    {
    public:
        Camera(fox::float32_t aspectRatio, fox::float32_t fov = 60.0f)
            : m_aspectRatio{ aspectRatio }, m_fov{ fov }, m_projection{ gfx::Projection::create<gfx::Projection::Type::Perspective>(m_aspectRatio, m_fov, 0.01f, 10000.0f) } {}
        virtual ~Camera() = default;

        float aspect_ratio() const
        {
            return m_aspectRatio;
        }
        float field_of_view() const
        {
            return m_fov;
        }
        const gfx::Projection& projection() const
        {
            return m_projection;
        }

    protected:
        fox::float32_t m_aspectRatio{};
        fox::float32_t m_fov{};

        gfx::Projection m_projection;

        Vector4f m_clearColor{ 0.0f, 0.0f, 0.0f, 1.0f };
    };
}
