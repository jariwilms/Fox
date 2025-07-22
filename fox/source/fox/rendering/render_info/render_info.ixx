export module fox.rendering.render_info;

import std;

import fox.core.transform;
import fox.core.types;
import fox.rendering.cubemap;
import fox.rendering.camera;
import fox.rendering.light;

export namespace fox::gfx
{
    struct RenderInfo
    {
        fox::Camera                                                  camera;
        fox::Transform                                               cameraTransform;
        std::span      <const std::tuple<fox::Light, fox::vector3f>> lights;
        std::shared_ptr<const gfx::Cubemap>                          skybox;
    };
}
