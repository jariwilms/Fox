#pragma once

#include "Component.hpp"

#include "Fox/Core/Library/Camera/Camera.hpp"

namespace fox
{
    class CameraComponent : public Camera, public Component
    {
    public:
        CameraComponent(Entity& parent)
            : Component{ parent } {}
    };
}
