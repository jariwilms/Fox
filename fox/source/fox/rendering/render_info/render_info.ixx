export module fox.rendering.render_info;

import std;
import fox.core.transform;
import fox.core.types;
import fox.rendering.cubemap;
import fox.rendering.camera;
import fox.rendering.light;

export namespace fox::gfx
{
    struct render_info
    {
        fox::vector2u                                                dimensions;
        fox::camera                                                  camera;
        fox::transform                                               cameraTransform;
        std::span      <const std::tuple<fox::light, fox::vector3f>> lights;
        std::shared_ptr<const gfx::cubemap>                          skybox;
    };
}
