#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Rendering.hpp"
#include "Helix/Rendering/API/OpenGL/OpenGLRenderer.hpp"

namespace hlx::gfx
{
    class Renderer
    {
    public:
        static void init()
        {
            s_renderer = std::make_unique<api::GRenderer<api::GraphicsAPI::OpenGL>>();
        }

        static void start()
        {
            s_renderer->start();
        }
        static void finish()
        {
            s_renderer->finish();
        }

        static void render()
        {
            //s_renderer->render();
        }

    private:
        static inline std::unique_ptr<api::GRenderer<api::GraphicsAPI::OpenGL>> s_renderer{};
    };
}
