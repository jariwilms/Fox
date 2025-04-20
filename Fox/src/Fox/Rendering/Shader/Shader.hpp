#pragma once

#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
#include "Fox/Rendering/GraphicsAPI/GraphicsAPI.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Shader/Shader.hpp"
#endif

namespace fox::gfx
{
    namespace impl
    {
#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
        using Shader = api::gl::Shader;
#endif
    }



    class Shader
    {
    public:
        using Stage = api::Shader::Stage;

        static inline auto create(Stage stage, std::span<const fox::byte_t> binary)
        {
            return std::shared_ptr<Shader>(new Shader{ stage, binary });
        }

        Stage         stage()  const
        {
            return _->stage();
        }
        gfx::handle_t handle() const
        {
            return _->handle();
        }

    protected:
        Shader(Stage stage, std::span<const fox::byte_t> binary)
            : _{ std::make_shared<impl::Shader>(stage, binary) } {}

        std::shared_ptr<impl::Shader> _;
    };
}
