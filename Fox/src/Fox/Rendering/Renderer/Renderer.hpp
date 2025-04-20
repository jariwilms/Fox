#pragma once

#include "Fox/Rendering/Renderer/OpenGLRenderer.hpp"

namespace fox::gfx
{
    class Renderer
    {
    public:
        static void init()
        {
            _ = std::make_unique<api::OpenGLRenderer>();
        }

        static void start(const gfx::RenderInfo& renderInfo)
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
        static inline std::unique_ptr<api::OpenGLRenderer> _;
    };
}
