#pragma once

#include "stdafx.hpp"

#include "Fox/Core/Library/Transform/Transform.hpp"
#include "Fox/Core/Library/Camera/Camera.hpp"
#include "Fox/Core/Library/Lighting/Light.hpp"
#include "Fox/Rendering/Using.hpp"

namespace fox::gfx
{
    struct RenderInfo
    {
        std::tuple<const fox::Camera&, const fox::Transform&> camera;
        std::span<const std::tuple<fox::Light, fox::Vector3f>> lights;

        gfx::CubemapTexture& skybox;
    };
}
