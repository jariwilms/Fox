//export module fox.rendering.renderer;

#include <fox/rendering/render_info/render_info.hpp>
#include <fox/rendering/mesh/Mesh.hpp>
#include <fox/rendering/material/Material.hpp>
#include <fox/core/transform/transform.hpp>

import std;
import fox.rendering.renderer.opengl;

auto FUCK = std::unique_ptr<fox::gfx::api::OpenGLRenderer>{};

namespace fox::gfx::renderer
{
    inline void init()
    {
        FUCK = std::make_unique<fox::gfx::api::OpenGLRenderer>();
    }

    inline void start(gfx::RenderInfo renderInfo)
    {
        FUCK->start(renderInfo);
    }
    inline void finish()
    {
        FUCK->finish();
    }

    inline void render(std::shared_ptr<const gfx::Mesh> mesh, std::shared_ptr<const gfx::Material> material, const fox::Transform& transform)
    {
        FUCK->render(mesh, material, transform);
    }
    inline void render_debug(const fox::Transform& transform)
    {
        FUCK->render_debug(transform);
    }

}
