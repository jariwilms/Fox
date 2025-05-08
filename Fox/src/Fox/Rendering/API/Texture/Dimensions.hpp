#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/Texture/Texture.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Core/Types.hpp"

namespace fox::gfx::api
{
    enum class Dimensions
    {
        _1D = 1, 
        _2D, 
        _3D, 
    };

    template<Dimensions> struct DimensionsToVectorMap;
    template<> struct DimensionsToVectorMap<Dimensions::_1D> { using type = fox::Vector1u; };
    template<> struct DimensionsToVectorMap<Dimensions::_2D> { using type = fox::Vector2u; };
    template<> struct DimensionsToVectorMap<Dimensions::_3D> { using type = fox::Vector3u; };

    template<Dimensions> struct DimensionsToWrappingMap;
    template<> struct DimensionsToWrappingMap<Dimensions::_1D>
    {
        struct wrap_t
        {
        public:
            wrap_t() = default;
            wrap_t(api::Texture::Wrapping wrapping)
                : s{ wrapping } {
            }

            api::Texture::Wrapping s;
        };
    };
    template<> struct DimensionsToWrappingMap<Dimensions::_2D>
    {
        struct wrap_t
        {
        public:
            wrap_t() = default;
            wrap_t(api::Texture::Wrapping wrapping)
                : wrap_t{ wrapping, wrapping } {
            }
            wrap_t(api::Texture::Wrapping wrappingS, api::Texture::Wrapping wrappingT)
                : s{ wrappingS }, t{ wrappingT } {
            }

            api::Texture::Wrapping s;
            api::Texture::Wrapping t;
        };
    };
    template<> struct DimensionsToWrappingMap<Dimensions::_3D>
    {
        struct wrap_t
        {
        public:
            wrap_t() = default;
            wrap_t(api::Texture::Wrapping wrapping)
                : wrap_t{ wrapping, wrapping, wrapping } {
            }
            wrap_t(api::Texture::Wrapping wrappingS, api::Texture::Wrapping wrappingT, api::Texture::Wrapping wrappingR)
                : s{ wrappingS }, t{ wrappingT }, r{ wrappingR } {
            }

            api::Texture::Wrapping s{};
            api::Texture::Wrapping t{};
            api::Texture::Wrapping r{};
        };
    };

    template<Dimensions> struct DimensionsToRangeMap;
    template<> struct DimensionsToRangeMap<Dimensions::_1D> { using type = gl::line_t  <gl::uint32_t>; };
    template<> struct DimensionsToRangeMap<Dimensions::_2D> { using type = gl::area_t  <gl::uint32_t>; };
    template<> struct DimensionsToRangeMap<Dimensions::_3D> { using type = gl::volume_t<gl::uint32_t>; };
}
