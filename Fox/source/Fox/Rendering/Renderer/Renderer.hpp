#pragma once

#include <fox/rendering/renderer/opengl_renderer.hpp>

namespace fox::gfx
{
    namespace impl
    {
#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
        using Renderer = api::OpenGLRenderer;
#endif
    }

    class Renderer
    {
    public:
        using renderer_t = impl::Renderer;

        static void init()
        {
            _ = std::make_unique<renderer_t>();
        }

        static void start(gfx::RenderInfo renderInfo)
        {
            _->start(renderInfo);
        }
        static void finish()
        {
            _->finish();
        }

        static void render(std::shared_ptr<const gfx::Mesh> mesh, std::shared_ptr<const gfx::Material> material, const fox::Transform& transform)
        {
            _->render(mesh, material, transform);
        }
        static void render_debug(const fox::Transform& transform)
        {
            _->render_debug(transform);
        }

    protected:
        static inline std::unique_ptr<renderer_t> _;
    };
}
