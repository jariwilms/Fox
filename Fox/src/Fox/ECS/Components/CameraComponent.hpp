#pragma once

#include "Fox/Core/Library/Camera/Camera.hpp"
#include "Fox/ECS/Components/Component.hpp"

namespace fox::ecs
{
    class CameraComponent : public Component
    {
    public:
        explicit CameraComponent(Entity& parent)
            : Component{ parent }, m_camera{ 16.0f / 9.0f } {}

        fox::Camera& camera()
        {
            return m_camera;
        }

    protected:
        fox::Camera m_camera;
    };
}
