#pragma once

#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
#include "Fox/Rendering/Shader/Shader.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Shader/Pipeline.hpp"
#include "Fox/Rendering/GraphicsAPI/GraphicsAPI.hpp"
#endif

namespace fox::gfx
{
    namespace impl
    {
#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
        template<typename T>
        using Pipeline = api::gl::Pipeline<T>;
#endif
    }



    class Pipeline
    {
    public:
        using Layout = impl::Pipeline<gfx::Shader>::Layout;

        static inline auto create(const Layout& layout)
        {
            return std::shared_ptr<Pipeline>(new Pipeline{ layout });
        }

        void bind()
        {
            _->bind();
        }

        gfx::handle_t handle() const
        {
            return _->handle();
        }

    protected:
        Pipeline(const Layout& layout)
            : _{ std::make_shared<impl::Pipeline<gfx::Shader>>(layout) } {}

        std::shared_ptr<impl::Pipeline<gfx::Shader>> _;
    };
}
