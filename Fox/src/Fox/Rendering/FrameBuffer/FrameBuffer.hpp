#pragma once

#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
#include "Fox/Rendering/GraphicsAPI/GraphicsAPI.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/FrameBuffer/FrameBuffer.hpp"
#endif

namespace fox::gfx
{
    namespace impl
    {
#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
        using FrameBuffer            = api::gl::FrameBuffer<api::AntiAliasing::None>;
        using FrameBufferMultisample = api::gl::FrameBuffer<api::AntiAliasing::MSAA>;
#endif
    }



    class FrameBuffer
    {
    public:
        using Target     = impl::FrameBuffer::Target;
        using Attachment = impl::FrameBuffer::Attachment;
        using Manifest   = impl::FrameBuffer::Manifest;

        static inline auto create(const fox::Vector2u& dimensions, std::span<const Manifest> manifests)
        {
            return std::shared_ptr<FrameBuffer>(new FrameBuffer{ dimensions, manifests });
        }

        void bind(Target target)
        {
            _->bind(target);
        }
        void bind_texture(const std::string& identifier, fox::uint32_t slot)
        {
            _->bind_texture(identifier, slot);
        }
        void bind_cubemap(const std::string& identifier, fox::uint32_t slot)
        {
            _->bind_cubemap(identifier, slot);
        }

        auto find_texture(const std::string& identifier)
        {
            return _->find_texture(identifier);
        }
        auto find_render_buffer(const std::string& identifier)
        {
            return _->find_render_buffer(identifier);
        }
        auto find_cubemap(const std::string& identifier)
        {
            return _->find_cubemap(identifier);
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
        FrameBuffer(const fox::Vector2u& dimensions, std::span<const Manifest> manifests)
            : _{ std::make_shared<impl::FrameBuffer>(dimensions, manifests) } {}

        std::shared_ptr<impl::FrameBuffer> _;
    };
    class FrameBufferMultisample
    {
    public:
        using Target     = impl::FrameBuffer::Target;
        using Attachment = impl::FrameBuffer::Attachment;
        using Manifest   = impl::FrameBuffer::Manifest;

        static inline auto create(const fox::Vector2u& dimensions, fox::uint8_t samples, std::span<const Manifest> manifests)
        {
            return std::shared_ptr<FrameBufferMultisample>(new FrameBufferMultisample{ dimensions, samples, manifests });
        }

        void bind(Target target)
        {
            _->bind(target);
        }
        void bind_texture(const std::string& identifier, fox::uint32_t slot)
        {
            _->bind_texture(identifier, slot);
        }

        auto find_texture(const std::string& identifier)
        {
            _->find_texture(identifier);
        }
        auto find_render_buffer(const std::string& identifier)
        {
            _->find_render_buffer(identifier);
        }

              fox::uint8_t   samples()    const
        {
            return _->samples();
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
        FrameBufferMultisample(const fox::Vector2u& dimensions, fox::uint8_t samples, std::span<const Manifest> manifests)
            : _{ std::make_shared<impl::FrameBufferMultisample>(dimensions, samples, manifests) } {}

        std::shared_ptr<impl::FrameBufferMultisample> _;
    };
}
