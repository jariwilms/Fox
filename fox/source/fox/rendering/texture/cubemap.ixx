export module fox.rendering.cubemap;

import std;
import fox.core.image;
import fox.core.meta;
import fox.core.types;
import fox.rendering.api;
import fox.rendering.base.cubemap;

export namespace fox::gfx
{
    class Cubemap
    {
    public:
        using Face      = api::Cubemap::Face;
        using Filter    = api::Cubemap::Filter;
        using Format    = api::Cubemap::Format;
        using Wrapping  = api::Cubemap::Wrapping;

        explicit Cubemap(std::shared_ptr<impl::Cubemap> _) 
            : _{ _ } {}

        static auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions) -> std::shared_ptr<gfx::Cubemap>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::Cubemap>>(std::in_place_t{}, format, filter, wrapping, dimensions);
        }
        static auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions, std::span<const fox::Image> faces) -> std::shared_ptr<gfx::Cubemap>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::Cubemap>>(std::in_place_t{}, format, filter, wrapping, dimensions, faces);
        }
        static auto create(Format format,                                   const fox::Vector2u& dimensions, std::span<const fox::Image> faces) -> std::shared_ptr<gfx::Cubemap>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::Cubemap>>(std::in_place_t{}, format, dimensions, faces);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(binding);
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
        auto dimensions   () const -> const fox::Vector2u&
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

    private:
        std::shared_ptr<impl::Cubemap> _;
    };
}
