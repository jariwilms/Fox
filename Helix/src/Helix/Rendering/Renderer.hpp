#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/RendererAPI.hpp"
#include "Helix/ECS/Components/Camera.hpp"
#include "Helix/Rendering/API/OpenGL/OpenGLRenderer.hpp"

namespace hlx
{
    class Renderer
    {
    public:
        static void init()
        {
            s_rendererAPI = std::make_shared<OpenGLRenderer>();
        }

        static void start(const RendererAPI::RenderInfo& renderInfo)
        {
            s_rendererAPI->start(renderInfo);
        }
        static void finish()
        {
            s_rendererAPI->finish();
        }

        //TODO: remove names => overload methods
        static void render_mesh(const std::shared_ptr<Mesh> mesh)
        {
            s_rendererAPI->render_mesh(mesh);
        }

    private:
        static inline std::shared_ptr<RendererAPI> s_rendererAPI{};
    };
}
