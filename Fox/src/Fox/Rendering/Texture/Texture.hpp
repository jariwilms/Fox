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
        using Texture1D            = api::gl::Texture<api::Dimensions::_1D, api::AntiAliasing::None>;
        using Texture2D            = api::gl::Texture<api::Dimensions::_2D, api::AntiAliasing::None>;
        using Texture3D            = api::gl::Texture<api::Dimensions::_3D, api::AntiAliasing::None>;

        using Texture2DMultisample = api::gl::Texture<api::Dimensions::_2D, api::AntiAliasing::MSAA>;
        using Texture3DMultisample = api::gl::Texture<api::Dimensions::_3D, api::AntiAliasing::MSAA>;
#endif
    }



    class Texture1D
    {
    public:
        using Format     = impl::Texture1D::Format;
        using Filter     = impl::Texture1D::Filter;
        using Wrapping   = impl::Texture1D::Wrapping;
        using Coordinate = impl::Texture1D::Coordinate;
        using wrap_t     = impl::Texture1D::wrap_t;
        using vector_t   = impl::Texture1D::vector_t;

        static inline auto create(Format format, const vector_t& dimensions, std::span<const fox::byte_t> data)
        {
            return std::shared_ptr<Texture1D>(new Texture1D{ format, dimensions, data });
        }
        static inline auto create(Format format, Filter filter, const wrap_t& wrapping, const vector_t& dimensions, std::span<const fox::byte_t> data)
        {
            return std::shared_ptr<Texture1D>(new Texture1D{ format, filter, wrapping, dimensions, data });
        }
        static inline auto create(Format format, Filter filter, const wrap_t& wrapping, const vector_t& dimensions)
        {
            return std::shared_ptr<Texture1D>(new Texture1D{ format, filter, wrapping, dimensions });
        }

        void bind(fox::uint32_t index) const
        {
            _->bind(index);
        }

        void copy(Format format, std::span<const fox::byte_t> data)
        {
            _->copy(format, data);
        }
        void copy_range(Format format, const vector_t& dimensions, const vector_t& offset, std::span<const fox::byte_t> data)
        {
            _->copy_range(format, dimensions, offset, data);
        }

        void apply_wrapping(const wrap_t& wrapping)
        {
            _->apply_wrapping(wrapping);
        }
        void generate_mipmap()
        {
            _->generate_mipmap();
        }

              Format        format()        const
        {
            return _->format();
        }
              Filter        filter()        const
        {
            return _->filter();
        }
              wrap_t        wrapping()      const
        {
            return _->wrapping();
        }
        const vector_t&     dimensions()    const
        {
            return _->dimensions();
        }
              fox::uint32_t mipmap_levels() const
        {
            return _->mipmap_levels();
        }
              gfx::handle_t handle()        const
        {
            return _->handle();
        }

    protected:
        Texture1D(Format format, const vector_t& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture1D>(format, dimensions, data) } {}
        Texture1D(Format format, Filter filter, const wrap_t& wrapping, const vector_t& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture1D>(format, filter, wrapping, dimensions, data) } {}
        Texture1D(Format format, Filter filter, const wrap_t& wrapping, const vector_t& dimensions)
            : _{ std::make_shared<impl::Texture1D>(format, filter, wrapping, dimensions) } {}

        std::shared_ptr<impl::Texture1D> _;
    };
    class Texture2D
    {
    public:
        using Format     = impl::Texture2D::Format;
        using Filter     = impl::Texture2D::Filter;
        using Wrapping   = impl::Texture2D::Wrapping;
        using Coordinate = impl::Texture2D::Coordinate;
        using wrap_t     = impl::Texture2D::wrap_t;
        using vector_t   = impl::Texture2D::vector_t;

        static inline auto create(Format format, const vector_t& dimensions, std::span<const fox::byte_t> data)
        {
            return std::shared_ptr<Texture2D>(new Texture2D{ format, dimensions, data });
        }
        static inline auto create(Format format, Filter filter, const wrap_t& wrapping, const vector_t& dimensions, std::span<const fox::byte_t> data)
        {
            return std::shared_ptr<Texture2D>(new Texture2D{ format, filter, wrapping, dimensions, data });
        }
        static inline auto create(Format format, Filter filter, const wrap_t& wrapping, const vector_t& dimensions)
        {
            return std::shared_ptr<Texture2D>(new Texture2D{ format, filter, wrapping, dimensions });
        }

        void bind(fox::uint32_t index) const
        {
            _->bind(index);
        }

        void copy(Format format, std::span<const fox::byte_t> data)
        {
            _->copy(format, data);
        }
        void copy_range(Format format, const vector_t& dimensions, const vector_t& offset, std::span<const fox::byte_t> data)
        {
            _->copy_range(format, dimensions, offset, data);
        }

        void apply_wrapping(const wrap_t& wrapping)
        {
            _->apply_wrapping(wrapping);
        }
        void generate_mipmap()
        {
            _->generate_mipmap();
        }

              Format        format()        const
        {
            return _->format();
        }
              Filter        filter()        const
        {
            return _->filter();
        }
              wrap_t        wrapping()      const
        {
            return _->wrapping();
        }
        const vector_t&     dimensions()    const
        {
            return _->dimensions();
        }
              fox::uint32_t mipmap_levels() const
        {
            return _->mipmap_levels();
        }
              gfx::handle_t handle()        const
        {
            return _->handle();
        }

    protected:
        Texture2D(Format format, const vector_t& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture2D>(format, dimensions, data) } {}
        Texture2D(Format format, Filter filter, const wrap_t& wrapping, const vector_t& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture2D>(format, filter, wrapping, dimensions, data) } {}
        Texture2D(Format format, Filter filter, const wrap_t& wrapping, const vector_t& dimensions)
            : _{ std::make_shared<impl::Texture2D>(format, filter, wrapping, dimensions) } {}

        std::shared_ptr<impl::Texture2D> _;
    };
    class Texture3D
    {
    public:
        using Format     = impl::Texture3D::Format;
        using Filter     = impl::Texture3D::Filter;
        using Wrapping   = impl::Texture3D::Wrapping;
        using Coordinate = impl::Texture3D::Coordinate;
        using wrap_t     = impl::Texture3D::wrap_t;
        using vector_t   = impl::Texture3D::vector_t;

        static inline auto create(Format format, const vector_t& dimensions, std::span<const fox::byte_t> data)
        {
            return std::shared_ptr<Texture3D>(new Texture3D{ format, dimensions, data });
        }
        static inline auto create(Format format, Filter filter, const wrap_t& wrapping, const vector_t& dimensions, std::span<const fox::byte_t> data)
        {
            return std::shared_ptr<Texture3D>(new Texture3D{ format, filter, wrapping, dimensions, data });
        }
        static inline auto create(Format format, Filter filter, const wrap_t& wrapping, const vector_t& dimensions)
        {
            return std::shared_ptr<Texture3D>(new Texture3D{ format, filter, wrapping, dimensions });
        }

        void bind(fox::uint32_t index) const
        {
            _->bind(index);
        }

        void copy(Format format, std::span<const fox::byte_t> data)
        {
            _->copy(format, data);
        }
        void copy_range(Format format, const vector_t& dimensions, const vector_t& offset, std::span<const fox::byte_t> data)
        {
            _->copy_range(format, dimensions, offset, data);
        }

        void apply_wrapping(const wrap_t& wrapping)
        {
            _->apply_wrapping(wrapping);
        }
        void generate_mipmap()
        {
            _->generate_mipmap();
        }

              Format        format()        const
        {
            return _->format();
        }
              Filter        filter()        const
        {
            return _->filter();
        }
              wrap_t        wrapping()      const
        {
            return _->wrapping();
        }
        const vector_t&     dimensions()    const
        {
            return _->dimensions();
        }
              fox::uint32_t mipmap_levels() const
        {
            return _->mipmap_levels();
        }
              gfx::handle_t handle()        const
        {
            return _->handle();
        }

    protected:
        Texture3D(Format format, const vector_t& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture3D>(format, dimensions, data) } {}
        Texture3D(Format format, Filter filter, const wrap_t& wrapping, const vector_t& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture3D>(format, filter, wrapping, dimensions, data) } {}
        Texture3D(Format format, Filter filter, const wrap_t& wrapping, const vector_t& dimensions)
            : _{ std::make_shared<impl::Texture3D>(format, filter, wrapping, dimensions) } {}

        std::shared_ptr<impl::Texture3D> _;
    };

    class Texture2DMultisample
    {
    public:
        using Format   = impl::Texture2DMultisample::Format;
        using vector_t = impl::Texture2DMultisample::vector_t;

        static inline auto create(Format format, const vector_t& dimensions, fox::uint8_t samples)
        {
            return std::shared_ptr<Texture2DMultisample>(new Texture2DMultisample{ format, dimensions, samples });
        }

        void bind(fox::uint32_t slot) const
        {
            _->bind(slot);
        }

              Format        format()     const
        {
            return _->format();
        }
              fox::uint8_t  samples()    const
        {
            return _->samples();
        }
        const vector_t&     dimensions() const
        {
            return _->dimensions();
        }
              gfx::handle_t handle()     const
        {
            return _->handle();
        }

    protected:
        Texture2DMultisample(Format format, const vector_t& dimensions, fox::uint8_t samples)
            : _{ std::make_shared<impl::Texture2DMultisample>(format, dimensions, samples) } {}

        std::shared_ptr<impl::Texture2DMultisample> _;
    };
    class Texture3DMultisample
    {
    public:
        using Format   = impl::Texture3DMultisample::Format;
        using vector_t = impl::Texture3DMultisample::vector_t;

        static inline auto create(Format format, const vector_t& dimensions, fox::uint8_t samples)
        {
            return std::shared_ptr<Texture3DMultisample>(new Texture3DMultisample{ format, dimensions, samples });
        }

        void bind(fox::uint32_t slot) const
        {
            _->bind(slot);
        }

              Format        format()     const
        {
            return _->format();
        }
              fox::uint8_t  samples()    const
        {
            return _->samples();
        }
        const vector_t&     dimensions() const
        {
            return _->dimensions();
        }
              gfx::handle_t handle()     const
        {
            return _->handle();
        }

    protected:
        Texture3DMultisample(Format format, const vector_t& dimensions, fox::uint8_t samples)
            : _{ std::make_shared<impl::Texture3DMultisample>(format, dimensions, samples) } {}

        std::shared_ptr<impl::Texture3DMultisample> _;
    };
}
