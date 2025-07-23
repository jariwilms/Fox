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
        using e_format   = api::Texture::Format;
        using e_filter   = api::Texture::Filter;
        using e_wrapping = api::Texture::Wrapping;

        explicit texture1d(std::shared_ptr<impl::Texture1D> _)
            : _{ _ } {}

        static auto create(e_format format, e_filter filter, e_wrapping wrapping, const fox::vector1u& dimensions) -> std::shared_ptr<gfx::texture1d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture1d>>(std::in_place_t{}, format, filter, wrapping, dimensions);
        }
        static auto create(e_format format, e_filter filter, e_wrapping wrapping, const fox::vector1u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<gfx::texture1d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture1d>>(std::in_place_t{}, format, filter, wrapping, dimensions, data);
        }
        static auto create(e_format format,                                   const fox::vector1u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<gfx::texture1d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture1d>>(std::in_place_t{}, format, dimensions, data);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(binding);
        }

        void copy      (e_format format,                       std::span<const fox::byte_t> data)
        {
            _->copy(format, data);
        }
        void copy_range(e_format format, fox::length_t region, std::span<const fox::byte_t> data)
        {
            _->copy_range(format, impl::length_t{ region.extent, region.origin }, data);
        }

        void apply_wrapping (e_wrapping s)
        {
            _->apply_wrapping({ s });
        }
        void generate_mipmap()
        {
            _->generate_mipmap();
        }

        auto format       () const -> e_format
        {
            return _->format();
        }
        auto filter       () const -> e_filter
        {
            return _->filter();
        }
        auto wrapping     () const -> const std::tuple<e_wrapping>&
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
        auto impl         () const -> std::shared_ptr<impl::Texture1D>
        {
            return _;
        }

    protected:
        texture1d(e_format format, e_filter filter, e_wrapping wrapping, const fox::vector1u& dimensions)
            : _{ std::make_shared<impl::Texture1D>(format, filter, wrapping, dimensions) } {}
        texture1d(e_format format, e_filter filter, e_wrapping wrapping, const fox::vector1u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture1D>(format, filter, wrapping, dimensions, data) } {}
        texture1d(e_format format,                                       const fox::vector1u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture1D>(format, dimensions, data) } {}

    private:
        std::shared_ptr<impl::Texture1D> _;
    };
    class texture2d
    {
    public:
        using e_format   = api::Texture::Format;
        using e_filter   = api::Texture::Filter;
        using e_wrapping = api::Texture::Wrapping;

        explicit texture2d(std::shared_ptr<impl::Texture2D> _)
            : _{ _ } {}

        static auto create(e_format format, e_filter filter, e_wrapping wrapping, const fox::vector2u& dimensions) -> std::shared_ptr<gfx::texture2d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture2d>>(std::in_place_t{}, format, filter, wrapping, dimensions);
        }
        static auto create(e_format format, e_filter filter, e_wrapping wrapping, const fox::vector2u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<gfx::texture2d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture2d>>(std::in_place_t{}, format, filter, wrapping, dimensions, data);
        }
        static auto create(e_format format,                                       const fox::vector2u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<gfx::texture2d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture2d>>(std::in_place_t{}, format, dimensions, data);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(binding);
        }

        void copy      (e_format format,                     std::span<const fox::byte_t> data)
        {
            _->copy(format, data);
        }
        void copy_range(e_format format, fox::area_t region, std::span<const fox::byte_t> data)
        {
            _->copy_range(format, impl::area_t{ region.extent, region.origin }, data);
        }

        void apply_wrapping (e_wrapping s, e_wrapping t)
        {
            _->apply_wrapping({ s, t });
        }
        void generate_mipmap()
        {
            _->generate_mipmap();
        }

        auto format       () const -> e_format
        {
            return _->format();
        }
        auto filter       () const -> e_filter
        {
            return _->filter();
        }
        auto wrapping     () const -> const std::tuple<e_wrapping, e_wrapping>&
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
        auto impl         () const -> std::shared_ptr<impl::Texture2D>
        {
            return _;
        }

    protected:
        texture2d(e_format format, e_filter filter, e_wrapping wrapping, const fox::vector2u& dimensions)
            : _{ std::make_shared<impl::Texture2D>(format, filter, wrapping, dimensions) } {}
        texture2d(e_format format, e_filter filter, e_wrapping wrapping, const fox::vector2u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture2D>(format, filter, wrapping, dimensions, data) } {}
        texture2d(e_format format,                                   const fox::vector2u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture2D>(format, dimensions, data) } {}

    private:
        std::shared_ptr<impl::Texture2D> _;
    };
    class texture3d
    {
    public:
        using e_format   = api::Texture::Format;
        using e_filter   = api::Texture::Filter;
        using e_wrapping = api::Texture::Wrapping;

        explicit texture3d(std::shared_ptr<impl::Texture3D> _)
            : _{ _ } {}

        static auto create(e_format format, e_filter filter, e_wrapping wrapping, const fox::vector3u& dimensions) -> std::shared_ptr<gfx::texture3d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture3d>>(std::in_place_t{}, format, filter, wrapping, dimensions);
        }
        static auto create(e_format format, e_filter filter, e_wrapping wrapping, const fox::vector3u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<gfx::texture3d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture3d>>(std::in_place_t{}, format, filter, wrapping, dimensions, data);
        }
        static auto create(e_format format,                                       const fox::vector3u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<gfx::texture3d>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture3d>>(std::in_place_t{}, format, dimensions, data);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(binding);
        }

        void copy      (e_format format,                       std::span<const fox::byte_t> data)
        {
            _->copy(format, data);
        }
        void copy_range(e_format format, fox::volume_t region, std::span<const fox::byte_t> data)
        {
            _->copy_range(format, impl::volume_t{ region.extent, region.origin }, data);
        }

        void apply_wrapping (e_wrapping s, e_wrapping t, e_wrapping r)
        {
            _->apply_wrapping({ s, t, r });
        }
        void generate_mipmap()
        {
            _->generate_mipmap();
        }

        auto format       () const -> e_format
        {
            return _->format();
        }
        auto filter       () const -> e_filter
        {
            return _->filter();
        }
        auto wrapping     () const -> const std::tuple<e_wrapping, e_wrapping, e_wrapping>&
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
        auto impl         () const -> std::shared_ptr<impl::Texture3D>
        {
            return _;
        }

    protected:
        texture3d(e_format format, e_filter filter, e_wrapping wrapping, const fox::vector3u& dimensions)
            : _{ std::make_shared<impl::Texture3D>(format, filter, wrapping, dimensions) } {}
        texture3d(e_format format, e_filter filter, e_wrapping wrapping, const fox::vector3u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture3D>(format, filter, wrapping, dimensions, data) } {}
        texture3d(e_format format,                                       const fox::vector3u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture3D>(format, dimensions, data) } {}

    private:
        std::shared_ptr<impl::Texture3D> _;
    };

    class texture2d_ms
    {
    public:
        using e_format = api::Texture::Format;

        explicit texture2d_ms(std::shared_ptr<impl::Texture2DMultisample> _)
            : _{ _ } {}

        static auto create(e_format format, const fox::vector2u& dimensions, fox::uint32_t samples) -> std::shared_ptr<gfx::texture2d_ms>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture2d_ms>>(std::in_place_t{}, format, dimensions, samples);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(binding);
        }

        auto format    () const -> e_format
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
        auto impl      () const -> std::shared_ptr<impl::Texture2DMultisample>
        {
            return _;
        }

    protected:
        texture2d_ms(e_format format, const fox::vector2u& dimensions, fox::uint32_t samples)
            : _{ std::make_shared<impl::Texture2DMultisample>(format, dimensions, samples) } {}

    private:
        std::shared_ptr<impl::Texture2DMultisample> _;
    };
    class texture3d_ms
    {
    public:
        using e_format = api::Texture::Format;

        explicit texture3d_ms(std::shared_ptr<impl::Texture3DMultisample> _)
            : _{ _ } {}

        static auto create(e_format format, const fox::vector3u& dimensions, fox::uint32_t samples) -> std::shared_ptr<gfx::texture3d_ms>
        {
            return std::make_shared<meta::from_inaccessible_ctor<gfx::texture3d_ms>>(std::in_place_t{}, format, dimensions, samples);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(binding);
        }

        auto format    () const -> e_format
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
        auto impl      () const -> std::shared_ptr<impl::Texture3DMultisample>
        {
            return _;
        }

    protected:
        texture3d_ms(e_format format, const fox::vector3u& dimensions, fox::uint32_t samples)
            : _{ std::make_shared<impl::Texture3DMultisample>(format, dimensions, samples) } {}

    private:
        std::shared_ptr<impl::Texture3DMultisample> _;
    };
}
