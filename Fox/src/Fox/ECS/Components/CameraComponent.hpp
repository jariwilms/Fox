#pragma once

#include "Component.hpp"

#include "Fox/Core/Library/Camera/Camera.hpp"

namespace fox
{
    class CameraComponent : public Component, public Camera
    {
    public:
        explicit CameraComponent(Entity& parent)
            : Component{ parent }, Camera{ 16.0f / 9.0f } {}
    };
}
