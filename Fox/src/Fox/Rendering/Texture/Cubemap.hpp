#pragma once

#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
#include "Fox/Rendering/GraphicsAPI/GraphicsAPI.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Texture/Cubemap.hpp"
#endif

namespace fox::gfx
{
    namespace impl
    {
#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
        using Cubemap = api::gl::Cubemap;
#endif
    }

    class Cubemap
    {
    public:
        using Format    = impl::Cubemap::Format;
        using Filter    = impl::Cubemap::Filter;
        using Wrapping  = impl::Cubemap::Wrapping;
        using Faces     = impl::Cubemap::Faces;
        using texture_t = impl::Cubemap::texture_t;

        static inline auto create(Format format, const fox::Vector2u& dimensions)
        {
            return std::shared_ptr<Cubemap>(new Cubemap{ format, dimensions });
        }
        static inline auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions)
        {
            return std::shared_ptr<Cubemap>(new Cubemap{ format, filter, wrapping, dimensions });
        }
        static inline auto create(Format format, const fox::Vector2u& dimensions, const Faces& face)
        {
            return std::shared_ptr<Cubemap>(new Cubemap{ format, dimensions, face });
        }
        static inline auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions, const Faces& face)
        {
            return std::shared_ptr<Cubemap>(new Cubemap{ format, filter, wrapping, dimensions, face });
        }

        void bind(fox::uint32_t index) const
        {
            _->bind(index);
        }

              Format         format()        const
        {
            return _->format();
        }
              Filter         filter()        const
        {
            return _->filter();
        }
              Wrapping       wrapping()      const
        {
            return _->wrapping();
        }
        const fox::Vector2u& dimensions()    const
        {
            return _->dimensions();
        }
              fox::uint32_t  mipmap_levels() const
        {
            return _->mipmap_levels();
        }
              gfx::handle_t  handle()        const
        {
            return _->handle();
        }

    protected:
        Cubemap(Format format, const fox::Vector2u& dimensions)
            : _{ std::make_shared<impl::Cubemap>(format, dimensions) } {}
        Cubemap(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions)
            : _{ std::make_shared<impl::Cubemap>(format, filter, wrapping, dimensions) } {}
        Cubemap(Format format, const fox::Vector2u& dimensions, const Faces& face)
            : _{ std::make_shared<impl::Cubemap>(format, dimensions, face) } {}
        Cubemap(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions, const Faces& face)
            : _{ std::make_shared<impl::Cubemap>(format, filter, wrapping, dimensions, face) } {}

        std::shared_ptr<impl::Cubemap> _;
    };
}
