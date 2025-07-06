#pragma once

#include <fox/rendering/api/api.hpp>

namespace fox::gfx
{
    class Cubemap
    {
    public:
        using Format    = impl::Cubemap::Format;
        using Filter    = impl::Cubemap::Filter;
        using Wrapping  = impl::Cubemap::Wrapping;
        using Face      = impl::Cubemap::Face;

        static inline auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions)
        {
            return std::shared_ptr<Cubemap>(new Cubemap{ format, filter, wrapping, dimensions });
        }
        static inline auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions, std::span<const fox::Image> faces)
        {
            return std::shared_ptr<Cubemap>(new Cubemap{ format, filter, wrapping, dimensions, faces });
        }
        static inline auto create(Format format,                                   const fox::Vector2u& dimensions, std::span<const fox::Image> faces)
        {
            return std::shared_ptr<Cubemap>(new Cubemap{ format, dimensions, faces });
        }

        Cubemap(std::shared_ptr<impl::Cubemap> cubemap)
            : _{ cubemap } {}

        void bind(gfx::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }

        void apply_wrapping (Wrapping s, Wrapping t)
        {
            _->apply_wrapping({ s, t });
        }
        void generate_mipmap()
        {
            _->generate_mipmap();
        }

        auto format       () const -> Format
        {
            return _->format();
        }
        auto filter       () const -> Filter
        {
            return _->filter();
        }
        auto wrapping     () const -> const std::tuple<Wrapping, Wrapping>&
        {
            return _->wrapping();
        }
        auto dimensions   () const -> fox::Vector2u
        {
            return _->dimensions();
        }
        auto mipmap_levels() const -> fox::uint32_t
        {
            return _->mipmap_levels();
        }
        auto handle       () const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl         () const -> std::shared_ptr<impl::Cubemap>
        {
            return _;
        }

    protected:
        Cubemap(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions)
            : _{ std::make_shared<impl::Cubemap>(format, filter, wrapping, dimensions) } {}
        Cubemap(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions, std::span<const fox::Image> faces)
            : _{ std::make_shared<impl::Cubemap>(format, filter, wrapping, dimensions, faces) } {}
        Cubemap(Format format,                                   const fox::Vector2u& dimensions, std::span<const fox::Image> faces)
            : _{ std::make_shared<impl::Cubemap>(format, dimensions, faces) } {}

        std::shared_ptr<impl::Cubemap> _;
    };
}
