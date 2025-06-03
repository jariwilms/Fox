#pragma once

#include "Fox/Rendering/GraphicsAPI/GraphicsAPI.hpp"
#include "Fox/Rendering/Texture/Texture.hpp"
#include "Fox/Rendering/Texture/Cubemap.hpp"
#include "Fox/Rendering/RenderBuffer/RenderBuffer.hpp"

#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
#include "Fox/Rendering/GraphicsAPI/OpenGL/FrameBuffer/FrameBuffer.hpp"
#endif

namespace fox::gfx
{
    namespace impl
    {
#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
        using index_t                = api::gl::index_t;
        
        using FrameBuffer            = api::gl::FrameBuffer;
        using FrameBufferMultisample = api::gl::FrameBufferMultisample;
#endif
    }



    class FrameBuffer
    {
    public:
        using Specification = impl::FrameBuffer::Specification;
        using Surface       = impl::FrameBuffer::Surface;
        using Target        = impl::FrameBuffer::Target;

        static inline auto create(const fox::Vector2u& dimensions, std::span<const Specification> specifications)
        {
            return std::shared_ptr<FrameBuffer>(new FrameBuffer{ dimensions, specifications });
        }

        void bind(Target target)
        {
            _->bind(target);
        }

        template<Surface A = Surface::Texture>
        auto surface(const std::string& identifier)
        {
            if constexpr (A == Surface::Texture)
            {
                return std::make_shared<gfx::Texture2D>(_->surface<A>(identifier));
            }
            if constexpr (A == Surface::Cubemap)
            {
                return std::make_shared<gfx::Cubemap>(_->surface<A>(identifier));
            }
            if constexpr (A == Surface::RenderBuffer)
            {
                return std::make_shared<gfx::RenderBuffer>(_->surface<A>(identifier));
            }
        }

        template<Surface A = Surface::Texture>
        void bind_surface(const std::string& identifier, fox::binding_t binding)
        {
            _->bind_surface<A>(identifier, static_cast<impl::binding_t>(binding));
        }

        void read_from(const std::string& identifier, fox::index_t index, fox::uint32_t level = 0u)
        {
            _->read_from(identifier, static_cast<impl::index_t>(index), level);
        }
        void write_to (const std::string& identifier, fox::index_t index, fox::uint32_t level = 0u)
        {
            _->write_to(identifier, static_cast<impl::index_t>(index), level);
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

        std::shared_ptr<impl::FrameBuffer>                               _;
        std::unordered_map<std::string, std::shared_ptr<gfx::Texture2D>> m_proxies{};
    };
    class FrameBufferMultisample
    {
    public:
        using Target        = impl::FrameBuffer::Target;
        using Attachment    = impl::FrameBuffer::Surface;
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
