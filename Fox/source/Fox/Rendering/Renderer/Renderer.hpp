#pragma once

#include <fox/rendering/renderer/opengl_renderer.hpp>

namespace fox::gfx::renderer
{
    namespace impl
    {
#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
        using renderer_t = gfx::api::OpenGLRenderer;
#endif
    }
    namespace api
    {
        inline std::unique_ptr<impl::renderer_t> renderer;
    }



    inline void init()
    {
        api::renderer = std::make_unique<impl::renderer_t>();
    }

    inline void start(gfx::RenderInfo renderInfo)
    {
        api::renderer->start(renderInfo);
    }
    inline void finish()
    {
        api::renderer->finish();
    }

    inline void render(std::shared_ptr<const gfx::Mesh> mesh, std::shared_ptr<const gfx::Material> material, const fox::Transform& transform)
    {
        api::renderer->render(mesh, material, transform);
    }
    inline void render_debug(const fox::Transform& transform)
    {
        api::renderer->render_debug(transform);
    }

}
