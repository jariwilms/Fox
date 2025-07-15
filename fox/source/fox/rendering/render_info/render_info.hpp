#pragma once

import std;

import fox.core.transform;
import fox.rendering.cubemap;
import fox.rendering.camera;
import fox.rendering.light;

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
