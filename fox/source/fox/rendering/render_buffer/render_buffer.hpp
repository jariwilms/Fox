#pragma once

#include <fox/rendering/api/render_buffer/render_buffer.hpp>
#include <fox/rendering/graphics_api/graphics_api.hpp>

namespace fox::gfx
{
    class RenderBuffer
    {
    public:
        using Format = api::RenderBuffer::Format;

        static inline auto create(Format format, const fox::Vector2u& dimensions)
        {
            return std::shared_ptr<RenderBuffer>(new RenderBuffer{ format, dimensions });
        }

        RenderBuffer(std::shared_ptr<impl::RenderBuffer> renderBuffer)
            : _{ renderBuffer } {}

        auto dimensions() const -> fox::Vector2u
        {
            return _->dimensions();
        }
        auto handle    () const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl      () const -> std::shared_ptr<impl::RenderBuffer>
        {
            return _;
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

        static inline auto create(Format format, const fox::Vector2u& dimensions, fox::uint32_t samples)
        {
            return std::shared_ptr<RenderBufferMultisample>(new RenderBufferMultisample{ format, dimensions, samples });
        }

        auto dimensions() const -> fox::Vector2u
        {
            return _->dimensions();
        }
        auto samples   () const -> fox::uint32_t
        {
            return _->samples();
        }
        auto handle    () const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl      () const -> std::shared_ptr<impl::RenderBufferMultisample>
        {
            return _;
        }

    protected:
        RenderBufferMultisample(Format format, const fox::Vector2u& dimensions, fox::uint32_t samples)
            : _{ std::make_shared<impl::RenderBufferMultisample>(format, dimensions, samples) } {}

        std::shared_ptr<impl::RenderBufferMultisample> _;
    };
}