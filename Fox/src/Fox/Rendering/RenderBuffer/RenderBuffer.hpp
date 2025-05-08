#pragma once

#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
#include "Fox/Rendering/GraphicsAPI/GraphicsAPI.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/RenderBuffer/RenderBuffer.hpp"
#endif

namespace fox::gfx
{
    namespace impl
    {
#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
        using RenderBuffer            = api::gl::RenderBuffer<api::AntiAliasing::None>;
        using RenderBufferMultisample = api::gl::RenderBuffer<api::AntiAliasing::MSAA>;
#endif
    }



    class RenderBuffer
    {
    public:
        using Format = api::RenderBuffer::Format;

        static inline auto create(Format format, const fox::Vector2u& dimensions)
        {
            return std::shared_ptr<RenderBuffer>(new RenderBuffer{ format, dimensions });
        }

        const fox::Vector2u& dimensions() const
        {
            return _->dimensions();
        }
              gfx::handle_t  handle()     const
        {
            return _->handle();
        }

    protected:
        RenderBuffer(Format format, const fox::Vector2u& dimensions)
            : _{ std::make_shared<impl::RenderBuffer>(format, dimensions) } {}

        std::shared_ptr<impl::RenderBuffer> _;
    };
    class RenderBufferMultisample
    {
    public:
        using Format = api::RenderBuffer::Format;

        static inline auto create(Format format, const fox::Vector2u& dimensions, fox::uint8_t samples)
        {
            return std::shared_ptr<RenderBufferMultisample>(new RenderBufferMultisample{ format, dimensions, samples });
        }

        const fox::Vector2u& dimensions() const
        {
            return _->dimensions();
        }
        fox::uint8_t         samples()    const
        {
            return _->samples();
        }
        gfx::handle_t        handle()     const
        {
            return _->handle();
        }

    protected:
        RenderBufferMultisample(Format format, const fox::Vector2u& dimensions, fox::uint8_t samples)
            : _{ std::make_shared<impl::RenderBufferMultisample>(format, dimensions, samples) } {}

        std::shared_ptr<impl::RenderBufferMultisample> _;
    };
}