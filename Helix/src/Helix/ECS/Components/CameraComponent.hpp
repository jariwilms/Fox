#pragma once

#include "Component.hpp"

#include "Helix/Core/Library/Camera/Camera.hpp"

namespace hlx
{
    class CameraComponent : public Camera, public Component
    {
    public:
        CameraComponent(Entity& parent)
            : Component{ parent } {}
    };
}
