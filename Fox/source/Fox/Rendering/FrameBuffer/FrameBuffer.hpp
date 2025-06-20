#pragma once

#include "Fox/Rendering/GraphicsAPI/GraphicsAPI.hpp"
#include "Fox/Rendering/RenderBuffer/RenderBuffer.hpp"
#include "Fox/Rendering/Texture/Cubemap.hpp"
#include "Fox/Rendering/Texture/Texture.hpp"

namespace fox::gfx
{
    class FrameBuffer
    {
    public:
        using Attachment    = api::FrameBuffer::Attachment;
        using Specification = api::FrameBuffer::Specification;
        using Surface       = api::FrameBuffer::Surface;
        using Target        = api::FrameBuffer::Target;

        static inline auto create(const fox::Vector2u& dimensions, std::span<const Specification> specifications)
        {
            return std::shared_ptr<FrameBuffer>(new FrameBuffer{ dimensions, specifications });
        }

        void bind(Target target)
        {
            _->bind(target);
        }
        template<Surface A = Surface::Texture>
        void bind_surface(const std::string& identifier, fox::binding_t binding)
        {
            _->bind_surface<A>(identifier, static_cast<impl::binding_t>(binding));
        }

        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gfx::Texture2D>    texture, fox::uint32_t level = 0u)
        {
            _->attach(identifier, attachment, texture->impl(), level);
        }
        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gfx::Cubemap>      cubemap, fox::uint32_t level = 0u)
        {
            _->attach(identifier, attachment, cubemap->impl(), level);
        }
        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gfx::RenderBuffer> renderBuffer)
        {
            _->attach(identifier, attachment, renderBuffer->impl());
        }

        template<Surface A = Surface::Texture>
        void detach(const std::string& identifier, Attachment attachment)
        {
            _->detach<A>(identifier, attachment);
        }
        
        void read_from(const std::string& identifier, fox::index_t index, fox::uint32_t level = 0u)
        {
            _->read_from(identifier, static_cast<impl::index_t>(index), level);
        }
        void write_to (const std::string& identifier, fox::index_t index, fox::uint32_t level = 0u)
        {
            _->write_to(identifier, static_cast<impl::index_t>(index), level);
        }

        void resize(const fox::Vector2u& dimensions)
        {
            _->resize(dimensions);
        }

        template<Surface A = Surface::Texture>
        auto surface   (const std::string& identifier)
        {
            if constexpr (A == Surface::Texture)      return std::make_shared<gfx::Texture2D>   (_->surface<A>(identifier));
            if constexpr (A == Surface::Cubemap)      return std::make_shared<gfx::Cubemap>     (_->surface<A>(identifier));
            if constexpr (A == Surface::RenderBuffer) return std::make_shared<gfx::RenderBuffer>(_->surface<A>(identifier));
        }
        auto attachment(Attachment attachment)
        {
            return _->attachment(attachment);
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
        using Target        = api::FrameBuffer::Target;
        using Attachment    = api::FrameBuffer::Surface;
        using Specification = api::FrameBuffer::Specification;

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
