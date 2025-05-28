#pragma once

#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
#include "Fox/Rendering/GraphicsAPI/GraphicsAPI.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Texture/Texture.hpp"
#endif

namespace fox::gfx
{
    namespace impl
    {
#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
        using binding_t            = api::gl::binding_t;

        using length_t             = api::gl::length_t;
        using area_t               = api::gl::area_t;
        using volume_t             = api::gl::volume_t;

        using Texture1D            = api::gl::Texture1D;
        using Texture2D            = api::gl::Texture2D;
        using Texture3D            = api::gl::Texture3D;

        using Texture2DMultisample = api::gl::Texture2DMultisample;
        using Texture3DMultisample = api::gl::Texture3DMultisample;
#endif
    }



    class Texture1D
    {
    public:
        using Format   = api::Texture::Format;
        using Filter   = api::Texture::Filter;
        using Wrapping = api::Texture::Wrapping;

        static inline auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector1u& dimensions)
        {
            return std::shared_ptr<Texture1D>(new Texture1D{ format, filter, wrapping, dimensions });
        }
        static inline auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector1u& dimensions, std::span<const fox::byte_t> data)
        {
            return std::shared_ptr<Texture1D>(new Texture1D{ format, filter, wrapping, dimensions, data });
        }
        static inline auto create(Format format,                                   const fox::Vector1u& dimensions, std::span<const fox::byte_t> data)
        {
            return std::shared_ptr<Texture1D>(new Texture1D{ format, dimensions, data });
        }

        Texture1D(std::shared_ptr<impl::Texture1D> texture)
            : _{ texture } {}

        void bind(fox::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }

        void copy      (Format format,                       std::span<const fox::byte_t> data)
        {
            _->copy(format, data);
        }
        void copy_range(Format format, fox::length_t region, std::span<const fox::byte_t> data)
        {
            _->copy_range(format, impl::length_t{ region.extent, region.origin }, data);
        }

        void apply_wrapping (Wrapping s)
        {
            _->apply_wrapping(s);
        }
        void generate_mipmap()
        {
            _->generate_mipmap();
        }

        auto format       () const
        {
            return _->format();
        }
        auto filter       () const
        {
            return _->filter();
        }
        auto wrapping     () const
        {
            return _->wrapping();
        }
        auto dimensions   () const
        {
            return _->dimensions();
        }
        auto mipmap_levels() const
        {
            return _->mipmap_levels();
        }
        auto handle       () const
        {
            return _->handle();
        }
        auto impl         () const
        {
            return _;
        }

    protected:
        Texture1D(Format format, Filter filter, Wrapping wrapping, const fox::Vector1u& dimensions)
            : _{ std::make_shared<impl::Texture1D>(format, filter, wrapping, dimensions) } {}
        Texture1D(Format format, Filter filter, Wrapping wrapping, const fox::Vector1u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture1D>(format, filter, wrapping, dimensions, data) } {}
        Texture1D(Format format,                                   const fox::Vector1u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture1D>(format, dimensions, data) } {}

        std::shared_ptr<impl::Texture1D> _;
    };
    class Texture2D
    {
    public:
        using Format   = api::Texture::Format;
        using Filter   = api::Texture::Filter;
        using Wrapping = api::Texture::Wrapping;

        static inline auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions)
        {
            return std::shared_ptr<Texture2D>(new Texture2D{ format, filter, wrapping, dimensions });
        }
        static inline auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions, std::span<const fox::byte_t> data)
        {
            return std::shared_ptr<Texture2D>(new Texture2D{ format, filter, wrapping, dimensions, data });
        }
        static inline auto create(Format format,                                   const fox::Vector2u& dimensions, std::span<const fox::byte_t> data)
        {
            return std::shared_ptr<Texture2D>(new Texture2D{ format, dimensions, data });
        }

        Texture2D(std::shared_ptr<impl::Texture2D> texture)
            : _{ texture } {}

        void bind(fox::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }

        void copy      (Format format,                     std::span<const fox::byte_t> data)
        {
            _->copy(format, data);
        }
        void copy_range(Format format, fox::area_t region, std::span<const fox::byte_t> data)
        {
            _->copy_range(format, impl::area_t{ region.extent, region.origin }, data);
        }

        void apply_wrapping (Wrapping s, Wrapping t)
        {
            _->apply_wrapping(s, t);
        }
        void generate_mipmap()
        {
            _->generate_mipmap();
        }

        auto format       () const
        {
            return _->format();
        }
        auto filter       () const
        {
            return _->filter();
        }
        auto wrapping     () const
        {
            return _->wrapping();
        }
        auto dimensions   () const
        {
            return _->dimensions();
        }
        auto mipmap_levels() const
        {
            return _->mipmap_levels();
        }
        auto handle       () const
        {
            return _->handle();
        }
        auto impl         () const
        {
            return _;
        }

    protected:
        Texture2D(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions)
            : _{ std::make_shared<impl::Texture2D>(format, filter, wrapping, dimensions) } {}
        Texture2D(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture2D>(format, filter, wrapping, dimensions, data) } {}
        Texture2D(Format format,                                   const fox::Vector2u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture2D>(format, dimensions, data) } {}

        std::shared_ptr<impl::Texture2D> _;
    };
    class Texture3D
    {
    public:
        using Format   = api::Texture::Format;
        using Filter   = api::Texture::Filter;
        using Wrapping = api::Texture::Wrapping;

        static inline auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector3u& dimensions)
        {
            return std::shared_ptr<Texture3D>(new Texture3D{ format, filter, wrapping, dimensions });
        }
        static inline auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector3u& dimensions, std::span<const fox::byte_t> data)
        {
            return std::shared_ptr<Texture3D>(new Texture3D{ format, filter, wrapping, dimensions, data });
        }
        static inline auto create(Format format,                                   const fox::Vector3u& dimensions, std::span<const fox::byte_t> data)
        {
            return std::shared_ptr<Texture3D>(new Texture3D{ format, dimensions, data });
        }

        Texture3D(std::shared_ptr<impl::Texture3D> texture)
            : _{ texture } {}

        void bind(fox::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }

        void copy      (Format format,                       std::span<const fox::byte_t> data)
        {
            _->copy(format, data);
        }
        void copy_range(Format format, fox::volume_t region, std::span<const fox::byte_t> data)
        {
            _->copy_range(format, impl::volume_t{ region.extent, region.origin }, data);
        }

        void apply_wrapping (Wrapping s, Wrapping t, Wrapping r)
        {
            _->apply_wrapping(s, t, r);
        }
        void generate_mipmap()
        {
            _->generate_mipmap();
        }

        auto format       () const
        {
            return _->format();
        }
        auto filter       () const
        {
            return _->filter();
        }
        auto wrapping     () const
        {
            return _->wrapping();
        }
        auto dimensions   () const
        {
            return _->dimensions();
        }
        auto mipmap_levels() const
        {
            return _->mipmap_levels();
        }
        auto handle       () const
        {
            return _->handle();
        }
        auto impl         () const
        {
            return _;
        }

    protected:
        Texture3D(Format format, Filter filter, Wrapping wrapping, const fox::Vector3u& dimensions)
            : _{ std::make_shared<impl::Texture3D>(format, filter, wrapping, dimensions) } {}
        Texture3D(Format format, Filter filter, Wrapping wrapping, const fox::Vector3u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture3D>(format, filter, wrapping, dimensions, data) } {}
        Texture3D(Format format,                                   const fox::Vector3u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture3D>(format, dimensions, data) } {}

        std::shared_ptr<impl::Texture3D> _;
    };

    class Texture2DMultisample
    {
    public:
        using Format = api::Texture::Format;

        static inline auto create(Format format, const fox::Vector2u& dimensions, fox::uint32_t samples)
        {
            return std::shared_ptr<Texture2DMultisample>(new Texture2DMultisample{ format, dimensions, samples });
        }

        void bind(fox::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }

        auto format    () const
        {
            return _->format();
        }
        auto samples   () const
        {
            return _->samples();
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
        Texture2DMultisample(Format format, const fox::Vector2u& dimensions, fox::uint32_t samples)
            : _{ std::make_shared<impl::Texture2DMultisample>(format, dimensions, samples) } {}

        std::shared_ptr<impl::Texture2DMultisample> _;
    };
    class Texture3DMultisample
    {
    public:
        using Format = api::Texture::Format;

        static inline auto create(Format format, const fox::Vector3u& dimensions, fox::uint32_t samples)
        {
            return std::shared_ptr<Texture3DMultisample>(new Texture3DMultisample{ format, dimensions, samples });
        }

        void bind(fox::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }

        auto format    () const
        {
            return _->format();
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
        Texture3DMultisample(Format format, const fox::Vector3u& dimensions, fox::uint32_t samples)
            : _{ std::make_shared<impl::Texture3DMultisample>(format, dimensions, samples) } {}

        std::shared_ptr<impl::Texture3DMultisample> _;
    };
}
