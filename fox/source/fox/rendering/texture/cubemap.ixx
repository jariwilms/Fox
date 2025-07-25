export module fox.rendering.cubemap;

import std;
import fox.core.image;
import fox.core.meta;
import fox.core.types;
import fox.rendering.api;
import fox.rendering.base.cubemap;

export namespace fox::gfx
{
    class cubemap
    {
    public:
        using face_e     = api::cubemap::face_e;
        using filter_e   = api::cubemap::filter_e;
        using format_e   = api::cubemap::format_e;
        using wrapping_e = api::cubemap::wrapping_e;

        explicit cubemap(std::shared_ptr<impl::cubemap> _) 
            : _{ _ } {}

        static auto create(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector2u& dimensions) -> std::shared_ptr<gfx::cubemap>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::cubemap>>(std::in_place_t{}, format, filter, wrapping, dimensions);
        }
        static auto create(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector2u& dimensions, std::span<const fox::image> faces) -> std::shared_ptr<gfx::cubemap>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::cubemap>>(std::in_place_t{}, format, filter, wrapping, dimensions, faces);
        }
        static auto create(format_e format,                                   const fox::vector2u& dimensions, std::span<const fox::image> faces) -> std::shared_ptr<gfx::cubemap>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::cubemap>>(std::in_place_t{}, format, dimensions, faces);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(binding);
        }

        void apply_wrapping (wrapping_e s, wrapping_e t)
        {
            _->apply_wrapping({ s, t });
        }
        void generate_mipmap()
        {
            _->generate_mipmap();
        }

        auto format       () const -> format_e
        {
            return _->format();
        }
        auto filter       () const -> filter_e
        {
            return _->filter();
        }
        auto wrapping     () const -> const std::tuple<wrapping_e, wrapping_e>&
        {
            return _->wrapping();
        }
        auto dimensions   () const -> const fox::vector2u&
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
        auto impl         () const -> std::shared_ptr<impl::cubemap>
        {
            return _;
        }

    protected:
        cubemap(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector2u& dimensions)
            : _{ std::make_shared<impl::cubemap>(format, filter, wrapping, dimensions) } {}
        cubemap(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector2u& dimensions, std::span<const fox::image> faces)
            : _{ std::make_shared<impl::cubemap>(format, filter, wrapping, dimensions, faces) } {}
        cubemap(format_e format,                                       const fox::vector2u& dimensions, std::span<const fox::image> faces)
            : _{ std::make_shared<impl::cubemap>(format, dimensions, faces) } {}

    private:
        std::shared_ptr<impl::cubemap> _;
    };
}
