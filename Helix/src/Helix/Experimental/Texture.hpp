#pragma once

#include "stdafx.hpp"

namespace gfx_test
{
    namespace imp
    {
        enum class GraphicsAPI
        {
            DirectX,
            Metal,
            OpenGL,
            Vulkan,
        };
        enum class Dimensions
        {
            _1D = 1,
            _2D,
            _3D,
        };
        enum class AntiAliasing
        {
            None,
            MSAA,
        };
        
        template<Dimensions D>
        struct DimensionToVector {};
        template<> struct DimensionToVector<Dimensions::_1D> { using type = Vector1u; };
        template<> struct DimensionToVector<Dimensions::_2D> { using type = Vector2u; };
        template<> struct DimensionToVector<Dimensions::_3D> { using type = Vector3u; };


        
        class Texture
        {
        public:
            enum class Format
            {
                //UNORM   => stored as unsigned integer, sampled as   floating point in range [      0,           1]
                //SNORM   => stored as   signed integer, sampled as   floating point in range [     -1,           1]
                //USCALED => stored as   floating point, sampled as   floating point in range [      0,    UINT_MAX]
                //SSCALED => stored as   floating point, sampled as   floating point in range [INT_MIN,     INT_MAX]
                //UINT    => stored as unsigned integer, sampled as unsigned integer in range [      0,    UINT_MAX]
                //SINT    => stored as   signed integer, sampled as   signed integer in range [INT_MIN,     INT_MAX]
                //UFLOAT  => stored as   floating point, sampled as   floating point in range [      0,  UFLOAT_MAX]
                //SFLOAT  => stored as   floating point, sampled as   floating point in range [FLOAT_MIN, FLOAT-MAX]
                //SRGB    => stored as unsigned integer, sampled as   floating point in range [      0,    UINT_MAX]
                //Note that the Red, Green and Blue components of SRGB values use nonlinear encoding

                R8_UNORM,
                RG8_UNORM,
                RGB8_UNORM,
                RGBA8_UNORM,

                R16_UNORM,
                RG16_UNORM,
                RGB16_UNORM,
                RGBA16_UNORM,

                R8_SNORM,
                RG8_SNORM,
                RGB8_SNORM,
                RGBA8_SNORM,

                R16_SNORM,
                RG16_SNORM,
                RGB16_SNORM,
                RGBA16_SNORM,

                R8_SRGB,
                RG8_SRGB,
                RGB8_SRGB,
                RGBA8_SRGB,

                R16_SFLOAT,
                RG16_SFLOAT,
                RGB16_SFLOAT,
                RGBA16_SFLOAT,

                R32_SFLOAT,
                RG32_SFLOAT,
                RGB32_SFLOAT,
                RGBA32_SFLOAT,

                D16_UNORM,
                D24_UNORM,
                D32_FLOAT,

                D24_UNORM_S8_UINT,
                D32_FLOAT_S8_UINT,

                S8_UINT,
            };
            enum class Filter
            {
                None,
                Point,
                Bilinear,
                Trilinear,
            };
            enum class Wrapping
            {
                ClampToEdge,
                ClampToBorder,

                Repeat,
                MirroredRepeat,
                MirroredClampToEdge,
            };

        protected:
            Texture(Format format, Filter filter, Wrapping wrapping)
                : m_format{ format }, m_filter{ filter }, m_wrapping{ wrapping } {}

            Format   m_format{};
            Filter   m_filter{};
            Wrapping m_wrapping{};
        };



        template<Dimensions D>
        class DTexture : public Texture
        {
        public:
            using Vector = DimensionToVector<D>::type;

            const Vector& dimensions() const
            {
                return m_dimensions;
            }

        protected:
            DTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const Vector& dimensions)
                : Texture{ format, filter, wrapping }, m_dimensions{ dimensions } {}

            Vector m_dimensions{};
        };



        template<GraphicsAPI G, Dimensions D, AntiAliasing A>
        class GTexture : public Texture {};
    }
}
