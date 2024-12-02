#pragma once

#include "stdafx.hpp"

#include "Dimensions.hpp"
#include "AntiAliasing.hpp"

namespace fox::gfx::api
{
    class Texture
    {
    public:
        enum class Format
        {
            //UNORM   => stored as unsigned integer, sampled as   floating point in range [        0,          1]
            //SNORM   => stored as   signed integer, sampled as   floating point in range [       -1,          1]
            //USCALED => stored as   floating point, sampled as   floating point in range [        0,   UINT_MAX]
            //SSCALED => stored as   floating point, sampled as   floating point in range [  INT_MIN,    INT_MAX]
            //UINT    => stored as unsigned integer, sampled as unsigned integer in range [        0,   UINT_MAX]
            //SINT    => stored as   signed integer, sampled as   signed integer in range [  INT_MIN,    INT_MAX]
            //UFLOAT  => stored as   floating point, sampled as   floating point in range [        0, UFLOAT_MAX]
            //SFLOAT  => stored as   floating point, sampled as   floating point in range [FLOAT_MIN,  FLOAT-MAX]
            //SRGB    => stored as unsigned integer, sampled as   floating point in range [        0,   UINT_MAX]
            //Note: The Red, Green and Blue components of SRGB formats are nonlinear

            //Format: 0x|Size 1|'|Size 2|'|No. Components|'|Primary Key|

            R8_UNORM = 		    0x08'00'01'00, 
            RG8_UNORM =         0x08'00'02'01, 
            RGB8_UNORM = 	    0x08'00'03'02, 
            RGBA8_UNORM = 	    0x08'00'04'03, //Recommended for regular images
                                
            R16_UNORM =         0x10'00'01'04, 
            RG16_UNORM = 	    0x10'00'02'05, 
            RGB16_UNORM = 	    0x10'00'03'06, 
            RGBA16_UNORM = 	    0x10'00'04'07, 
                                
            R8_SNORM = 		    0x08'00'01'08, 
            RG8_SNORM = 	    0x08'00'02'09, 
            RGB8_SNORM = 	    0x08'00'03'0A, 
            RGBA8_SNORM = 	    0x08'00'04'0B, //Recommended for normal maps
                                
            R16_SNORM = 	    0x10'00'01'0C, 
            RG16_SNORM = 	    0x10'00'02'0D, 
            RGB16_SNORM = 	    0x10'00'03'0E, 
            RGBA16_SNORM = 	    0x10'00'04'0F, 
                                
            R8_SRGB = 		    0x08'00'01'10, 
            RG8_SRGB = 		    0x08'00'02'11, 
            RGB8_SRGB =         0x08'00'03'12, 
            RGBA8_SRGB = 	    0x08'00'04'13, //Recommended for sRGB images
                                
            R16_SFLOAT = 	    0x10'00'01'14, 
            RG16_SFLOAT = 	    0x10'00'02'15, 
            RGB16_SFLOAT = 	    0x10'00'03'16, 
            RGBA16_SFLOAT =     0x10'00'04'17, 
                                
            R32_SFLOAT = 	    0x20'00'01'18, 
            RG32_SFLOAT = 	    0x20'00'02'19, 
            RGB32_SFLOAT = 	    0x20'00'03'1A, 
            RGBA32_SFLOAT =     0x20'00'04'1B, 
                                
            D16_UNORM =         0x10'00'10'1C, 
            D24_UNORM =         0x18'00'10'1D, 
            D32_FLOAT =         0x20'00'10'1E, 
                                
            S8_UINT = 		    0x08'00'20'1F, 

            D24_UNORM_S8_UINT = 0x18'08'30'20, 
            D32_FLOAT_S8_UINT = 0x20'08'30'21, 
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
}
