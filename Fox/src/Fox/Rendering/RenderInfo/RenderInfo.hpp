#pragma once

#include "stdafx.hpp"

#include "Helix/Core/Library/Transform/Transform.hpp"
#include "Helix/Core/Library/Camera/Camera.hpp"
#include "Helix/Core/Library/Lighting/Light.hpp"

namespace hlx::gfx
{
    struct RenderInfo
    {
        std::tuple<const Camera&, const Transform&> camera;
        std::span<const std::tuple<Light, Vector3f>, 32> lights;
    };
}
