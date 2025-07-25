export module fox.rendering.texture;

import std;
import fox.core.types;
import fox.core.meta;
import fox.rendering.api;
import fox.rendering.base.texture;

export namespace fox::gfx
{
    class texture1d
    {
    public:
        using format_e   = api::Texture::format_e;
        using filter_e   = api::Texture::filter_e;
        using wrapping_e = api::Texture::wrapping_e;

        explicit texture1d(std::shared_ptr<impl::texture1d> _)
            : _{ _ } {}

        static auto create(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector1u& dimensions) -> std::shared_ptr<gfx::texture1d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture1d>>(std::in_place_t{}, format, filter, wrapping, dimensions);
        }
        static auto create(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector1u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<gfx::texture1d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture1d>>(std::in_place_t{}, format, filter, wrapping, dimensions, data);
        }
        static auto create(format_e format,                                   const fox::vector1u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<gfx::texture1d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture1d>>(std::in_place_t{}, format, dimensions, data);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(binding);
        }

        void copy      (format_e format,                       std::span<const fox::byte_t> data)
        {
            _->copy(format, data);
        }
        void copy_range(format_e format, fox::length_t region, std::span<const fox::byte_t> data)
        {
            _->copy_range(format, impl::length_t{ region.extent, region.origin }, data);
        }

        void apply_wrapping (wrapping_e s)
        {
            _->apply_wrapping({ s });
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
        auto wrapping     () const -> const std::tuple<wrapping_e>&
        {
            return _->wrapping();
        }
        auto dimensions   () const -> const fox::vector1u&
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
        auto impl         () const -> std::shared_ptr<impl::texture1d>
        {
            return _;
        }

    protected:
        texture1d(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector1u& dimensions)
            : _{ std::make_shared<impl::texture1d>(format, filter, wrapping, dimensions) } {}
        texture1d(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector1u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::texture1d>(format, filter, wrapping, dimensions, data) } {}
        texture1d(format_e format,                                       const fox::vector1u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::texture1d>(format, dimensions, data) } {}

    private:
        std::shared_ptr<impl::texture1d> _;
    };
    class texture2d
    {
    public:
        using format_e   = api::Texture::format_e;
        using filter_e   = api::Texture::filter_e;
        using wrapping_e = api::Texture::wrapping_e;

        explicit texture2d(std::shared_ptr<impl::texture2d> _)
            : _{ _ } {}

        static auto create(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector2u& dimensions) -> std::shared_ptr<gfx::texture2d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture2d>>(std::in_place_t{}, format, filter, wrapping, dimensions);
        }
        static auto create(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector2u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<gfx::texture2d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture2d>>(std::in_place_t{}, format, filter, wrapping, dimensions, data);
        }
        static auto create(format_e format,                                       const fox::vector2u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<gfx::texture2d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture2d>>(std::in_place_t{}, format, dimensions, data);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(binding);
        }

        void copy      (format_e format,                     std::span<const fox::byte_t> data)
        {
            _->copy(format, data);
        }
        void copy_range(format_e format, fox::area_t region, std::span<const fox::byte_t> data)
        {
            _->copy_range(format, impl::area_t{ region.extent, region.origin }, data);
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
        auto impl         () const -> std::shared_ptr<impl::texture2d>
        {
            return _;
        }

    protected:
        texture2d(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector2u& dimensions)
            : _{ std::make_shared<impl::texture2d>(format, filter, wrapping, dimensions) } {}
        texture2d(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector2u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::texture2d>(format, filter, wrapping, dimensions, data) } {}
        texture2d(format_e format,                                   const fox::vector2u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::texture2d>(format, dimensions, data) } {}

    private:
        std::shared_ptr<impl::texture2d> _;
    };
    class texture3d
    {
    public:
        using format_e   = api::Texture::format_e;
        using filter_e   = api::Texture::filter_e;
        using wrapping_e = api::Texture::wrapping_e;

        explicit texture3d(std::shared_ptr<impl::texture3d> _)
            : _{ _ } {}

        static auto create(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector3u& dimensions) -> std::shared_ptr<gfx::texture3d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture3d>>(std::in_place_t{}, format, filter, wrapping, dimensions);
        }
        static auto create(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector3u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<gfx::texture3d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture3d>>(std::in_place_t{}, format, filter, wrapping, dimensions, data);
        }
        static auto create(format_e format,                                       const fox::vector3u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<gfx::texture3d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture3d>>(std::in_place_t{}, format, dimensions, data);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(binding);
        }

        void copy      (format_e format,                       std::span<const fox::byte_t> data)
        {
            _->copy(format, data);
        }
        void copy_range(format_e format, fox::volume_t region, std::span<const fox::byte_t> data)
        {
            _->copy_range(format, impl::volume_t{ region.extent, region.origin }, data);
        }

        void apply_wrapping (wrapping_e s, wrapping_e t, wrapping_e r)
        {
            _->apply_wrapping({ s, t, r });
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
        auto wrapping     () const -> const std::tuple<wrapping_e, wrapping_e, wrapping_e>&
        {
            return _->wrapping();
        }
        auto dimensions   () const -> const fox::vector3u&
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
        auto impl         () const -> std::shared_ptr<impl::texture3d>
        {
            return _;
        }

    protected:
        texture3d(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector3u& dimensions)
            : _{ std::make_shared<impl::texture3d>(format, filter, wrapping, dimensions) } {}
        texture3d(format_e format, filter_e filter, wrapping_e wrapping, const fox::vector3u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::texture3d>(format, filter, wrapping, dimensions, data) } {}
        texture3d(format_e format,                                       const fox::vector3u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::texture3d>(format, dimensions, data) } {}

    private:
        std::shared_ptr<impl::texture3d> _;
    };

    class texture2d_ms
    {
    public:
        using format_e = api::Texture::format_e;

        explicit texture2d_ms(std::shared_ptr<impl::texture2d_ms> _)
            : _{ _ } {}

        static auto create(format_e format, const fox::vector2u& dimensions, fox::uint32_t samples) -> std::shared_ptr<gfx::texture2d_ms>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture2d_ms>>(std::in_place_t{}, format, dimensions, samples);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(binding);
        }

        auto format    () const -> format_e
        {
            return _->format();
        }
        auto samples   () const -> fox::uint32_t
        {
            return _->samples();
        }
        auto dimensions() const -> const fox::vector2u&
        {
            return _->dimensions();
        }
        auto handle    () const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl      () const -> std::shared_ptr<impl::texture2d_ms>
        {
            return _;
        }

    protected:
        texture2d_ms(format_e format, const fox::vector2u& dimensions, fox::uint32_t samples)
            : _{ std::make_shared<impl::texture2d_ms>(format, dimensions, samples) } {}

    private:
        std::shared_ptr<impl::texture2d_ms> _;
    };
    class texture3d_ms
    {
    public:
        using format_e = api::Texture::format_e;

        explicit texture3d_ms(std::shared_ptr<impl::texture3d_ms> _)
            : _{ _ } {}

        static auto create(format_e format, const fox::vector3u& dimensions, fox::uint32_t samples) -> std::shared_ptr<gfx::texture3d_ms>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture3d_ms>>(std::in_place_t{}, format, dimensions, samples);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(binding);
        }

        auto format    () const -> format_e
        {
            return _->format();
        }
        auto dimensions() const -> const fox::vector3u&
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
        auto impl      () const -> std::shared_ptr<impl::texture3d_ms>
        {
            return _;
        }

    protected:
        texture3d_ms(format_e format, const fox::vector3u& dimensions, fox::uint32_t samples)
            : _{ std::make_shared<impl::texture3d_ms>(format, dimensions, samples) } {}

    private:
        std::shared_ptr<impl::texture3d_ms> _;
    };
}
