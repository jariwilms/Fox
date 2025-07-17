export module fox.rendering.renderer;

import std;
import fox.core.transform;
import fox.rendering.material;
import fox.rendering.mesh;
import fox.rendering.model;
import fox.rendering.render_info;
import fox.rendering.renderer.opengl;

auto renderer_ = std::unique_ptr<fox::gfx::api::OpenGLRenderer>{};

export namespace fox::gfx::renderer
{
    inline void init()
    {
        renderer_ = std::make_unique<fox::gfx::api::OpenGLRenderer>();
    }

    inline void start(gfx::RenderInfo renderInfo)
    {
        renderer_->start(renderInfo);
    }
    inline void finish()
    {
        renderer_->finish();
    }

    inline void render(std::shared_ptr<const gfx::Mesh> mesh, std::shared_ptr<const gfx::Material> material, const fox::Transform& transform)
    {
        renderer_->render(mesh, material, transform);
    }
    inline void render_debug(const fox::Transform& transform)
    {
        renderer_->render_debug(transform);
    }
}
