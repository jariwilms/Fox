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

        void bind(fox::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
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
        Cubemap(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions)
            : _{ std::make_shared<impl::Cubemap>(format, filter, wrapping, dimensions) } {}
        Cubemap(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions, std::span<const fox::Image> faces)
            : _{ std::make_shared<impl::Cubemap>(format, filter, wrapping, dimensions, faces) } {}
        Cubemap(Format format,                                   const fox::Vector2u& dimensions, std::span<const fox::Image> faces)
            : _{ std::make_shared<impl::Cubemap>(format, dimensions, faces) } {}

        std::shared_ptr<impl::Cubemap> _;
    };
}
