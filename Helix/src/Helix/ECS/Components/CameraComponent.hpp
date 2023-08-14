#pragma once

#include "Component.hpp"

#include "Helix/Core/Library/Camera/Camera.hpp"

namespace hlx
{
    struct CameraComponent : public Component
    {
    public:
        CameraComponent() = default;
        virtual ~CameraComponent() = default;

        operator Camera&()
        {
            return m_camera;
        }
        operator const Camera&() const
        {
            return m_camera;
        }
        
    protected:
        Camera m_camera{};
    };
}
