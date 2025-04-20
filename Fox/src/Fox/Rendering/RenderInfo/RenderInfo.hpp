#pragma once

#include "stdafx.hpp"

#include "Fox/Core/Library/Transform/Transform.hpp"
#include "Fox/Core/Library/Camera/Camera.hpp"
#include "Fox/Core/Library/Lighting/Light.hpp"
#include "Fox/Rendering/Texture/Cubemap.hpp"

namespace fox::gfx
{
    //A simple view class for a scene's camera, lights, and skybox
    struct RenderInfo
    {
        std::tuple<const fox::Camera&, const fox::Transform&>  camera;
        std::span<const std::tuple<fox::Light, fox::Vector3f>> lights;
        std::shared_ptr<const gfx::Cubemap>                    skybox;
    };
}
