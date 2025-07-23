export module fox.rendering.render_buffer;

import std;
import fox.core.types;
import fox.core.meta;
import fox.rendering.api;
import fox.rendering.base.render_buffer;

export namespace fox::gfx
{
    class render_buffer
    {
    public:
        using format_e = api::RenderBuffer::Format;

        explicit render_buffer(std::shared_ptr<impl::RenderBuffer> _)
            : _{ _ } {}

        static auto create(format_e format, const fox::vector2u& dimensions) -> std::shared_ptr<gfx::render_buffer>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::render_buffer>>(std::in_place_t{}, format, dimensions);
        }

        auto dimensions() const -> const fox::vector2u&
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
        render_buffer(format_e format, const fox::vector2u& dimensions)
            : _{ std::make_shared<impl::RenderBuffer>(format, dimensions) } {}

    private:
        std::shared_ptr<impl::RenderBuffer> _;
    };
    class render_buffer_ms
    {
    public:
        using format_e = api::RenderBuffer::Format;

        explicit render_buffer_ms(std::shared_ptr<impl::RenderBufferMultisample> _)
            : _{ _ } {}

        static auto create(format_e format, const fox::vector2u& dimensions, fox::uint32_t samples) -> std::shared_ptr<gfx::render_buffer_ms>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::render_buffer_ms>>(std::in_place_t{}, format, dimensions, samples);
        }

        auto dimensions() const -> const fox::vector2u&
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
        render_buffer_ms(format_e format, const fox::vector2u& dimensions, fox::uint32_t samples)
            : _{ std::make_shared<impl::RenderBufferMultisample>(format, dimensions, samples) } {}

    private:
        std::shared_ptr<impl::RenderBufferMultisample> _;
    };
}