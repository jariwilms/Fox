export module fox.rendering.renderer;

import std;
import fox.core.transform;
import fox.rendering.renderer.opengl;
import fox.rendering;

auto renderer_ = std::unique_ptr<fox::gfx::api::OpenGLRenderer>{};

export namespace fox::gfx::renderer
{
    void init()
    {
        renderer_ = std::make_unique<fox::gfx::api::OpenGLRenderer>();
    }

    void start(gfx::render_info renderInfo)
    {
        renderer_->start(renderInfo);
    }
    void finish()
    {
        renderer_->finish();
    }

    void render(std::shared_ptr<const gfx::mesh> mesh, std::shared_ptr<const gfx::material> material, const fox::transform& transform)
    {
        renderer_->render(mesh, material, transform);
    }
    void render_debug(const fox::transform& transform)
    {
        renderer_->render_debug(transform);
    }
}
