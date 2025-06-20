#pragma once

#include <memory>
#include <tuple>

#include <fox/core/types/rendering/camera/camera.hpp>
#include <fox/core/types/rendering/light/light.hpp>
#include <fox/core/types/transform/transform.hpp>
#include <fox/rendering/texture/cubemap.hpp>

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
