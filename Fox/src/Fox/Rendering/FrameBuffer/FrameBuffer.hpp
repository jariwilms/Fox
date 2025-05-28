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
        using FrameBuffer            = api::gl::FrameBuffer;
        using FrameBufferMultisample = api::gl::FrameBufferMultisample;
#endif
    }



    class FrameBuffer
    {
    public:
        using Target        = impl::FrameBuffer::Target;
        using Attachment    = impl::FrameBuffer::Attachment;
        using Specification = impl::FrameBuffer::Specification;

        static inline auto create(const fox::Vector2u& dimensions, std::span<const Specification> specifications)
        {
            return std::shared_ptr<FrameBuffer>(new FrameBuffer{ dimensions, specifications });
        }

        void bind(Target target)
        {
            _->bind(target);
        }
        void bind_texture(const std::string& identifier, fox::binding_t binding)
        {
            _->bind_texture(identifier, static_cast<impl::binding_t>(binding));
        }
        void bind_cubemap(const std::string& identifier, fox::binding_t binding)
        {
            _->bind_cubemap(identifier, static_cast<impl::binding_t>(binding));
        }

        auto find_texture      (const std::string& identifier)
        {
            return _->find_texture(identifier);
        }
        auto find_render_buffer(const std::string& identifier)
        {
            return _->find_render_buffer(identifier);
        }
        auto find_cubemap      (const std::string& identifier)
        {
            return _->find_cubemap(identifier);
        }

        auto dimensions() const
        {
            return _->dimensions();
        }
        auto handle    () const
        {
            return _->handle();
        }
        auto impl      () const
        {
            return _;
        }

    protected:
        FrameBuffer(const fox::Vector2u& dimensions, std::span<const Specification> specifications)
            : _{ std::make_shared<impl::FrameBuffer>(dimensions, specifications) } {}

        std::shared_ptr<impl::FrameBuffer> _;
    };
    class FrameBufferMultisample
    {
    public:
        using Target        = impl::FrameBuffer::Target;
        using Attachment    = impl::FrameBuffer::Attachment;
        using Specification = impl::FrameBuffer::Specification;

        static inline auto create(const fox::Vector2u& dimensions, std::span<const Specification> specifications, fox::uint32_t samples)
        {
            return std::shared_ptr<FrameBufferMultisample>(new FrameBufferMultisample{ dimensions, specifications, samples });
        }

        void bind(Target target)
        {
            _->bind(target);
        }
        void bind_texture(const std::string& identifier, fox::binding_t binding)
        {
            _->bind_texture(identifier, static_cast<impl::binding_t>(binding));
        }

        auto find_texture      (const std::string& identifier)
        {
            _->find_texture(identifier);
        }
        auto find_render_buffer(const std::string& identifier)
        {
            _->find_render_buffer(identifier);
        }

        auto dimensions() const
        {
            return _->dimensions();
        }
        auto samples   () const
        {
            return _->samples();
        }
        auto handle    () const
        {
            return _->handle();
        }
        auto impl      () const
        {
            return _;
        }

    protected:
        FrameBufferMultisample(const fox::Vector2u& dimensions, std::span<const Specification> specifications, fox::uint32_t samples)
            : _{ std::make_shared<impl::FrameBufferMultisample>(dimensions, specifications, samples) } {}

        std::shared_ptr<impl::FrameBufferMultisample> _;
    };
}
