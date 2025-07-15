module;

#include <fox/rendering/api/api.hpp>
#include <fox/rendering/base/render_buffer/render_buffer.hpp>

export module fox.rendering.render_buffer;

export namespace fox::gfx
{
    class RenderBuffer
    {
    public:
        using Format = api::RenderBuffer::Format;

        RenderBuffer(std::shared_ptr<impl::RenderBuffer> _)
            : _{ _ } {}

        static auto create(Format format, const fox::Vector2u& dimensions) -> std::shared_ptr<gfx::RenderBuffer>
        {
            return std::make_shared<fox::from_inaccessible_ctor<gfx::RenderBuffer>>(format, dimensions);
        }

        auto dimensions() const -> const fox::Vector2u&
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

        RenderBufferMultisample(std::shared_ptr<impl::RenderBufferMultisample> _)
            : _{ _ } {}

        static auto create(Format format, const fox::Vector2u& dimensions, fox::uint32_t samples) -> std::shared_ptr<gfx::RenderBufferMultisample>
        {
            return std::make_shared<fox::from_inaccessible_ctor<gfx::RenderBufferMultisample>>(format, dimensions, samples);
        }

        auto dimensions() const -> const fox::Vector2u&
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