#pragma once

#include "stdafx.hpp"

#include "Fox/Core/Library/Transform/Transform.hpp"
#include "Fox/Core/Library/Camera/Camera.hpp"
#include "Fox/Core/Library/Lighting/Light.hpp"

namespace fox::gfx
{
    struct RenderInfo
    {
        std::tuple<const Camera&, const Transform&> camera;
        std::span<const std::tuple<Light, Vector3f>, 32> lights;
    };
}
