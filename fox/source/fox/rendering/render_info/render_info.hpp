#pragma once

#include <stdafx.hpp>

#include <fox/rendering/light/light.hpp>

import fox.core.transform;
import fox.rendering.cubemap;
import fox.rendering.camera;

namespace fox::gfx
{
    struct RenderInfo
    {
        fox::Camera                                                  camera;
        fox::Transform                                               cameraTransform;
        std::span      <const std::tuple<fox::Light, fox::Vector3f>> lights;
        std::shared_ptr<const gfx::Cubemap>                          skybox;
    };
}
