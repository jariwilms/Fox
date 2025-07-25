export module fox.rendering.base.cubemap;

import fox.rendering.base.texture;

export namespace fox::gfx::api
{
	struct cubemap
	{
        enum class format_e
        {
            //UNORM => stored as unsigned integer, sampled             as floating point   in range [        0,         1]
            //SNORM => stored as   signed integer, sampled             as floating point   in range [       -1,         1]
            //SRGB  => stored as unsigned integer, sampled nonlinearly as floating point   in range [        0,  UINT_MAX]
            //UINT  => stored as unsigned integer, sampled             as unsigned integer in range [        0,  UINT_MAX]
            //FLOAT => stored as   floating point, sampled             as floating point   in range [FLOAT_MIN, FLOAT_MAX]

            //Format: 0x|First component size|'|Second component size|'|No. components|'|Primary key|

            r8_unorm          = 0x08'00'01'00, 
            rg8_unorm         = 0x08'00'02'01, 
            rgb8_unorm        = 0x08'00'03'02, 
            rgba8_unorm       = 0x08'00'04'03, //Recommended for color images
                                     
            r16_unorm         = 0x10'00'01'04, 
            rg16_unorm        = 0x10'00'02'05, 
            rgb16_unorm       = 0x10'00'03'06, 
            rgba16_unorm      = 0x10'00'04'07, 
                                     
            r8_snorm          = 0x08'00'01'08, 
            rg8_snorm         = 0x08'00'02'09, 
            rgb8_snorm        = 0x08'00'03'0A, 
            rgba8_snorm       = 0x08'00'04'0B, //Recommended for normal maps
                                     
            r16_snorm         = 0x10'00'01'0C, 
            rg16_snorm        = 0x10'00'02'0D, 
            rgb16_snorm       = 0x10'00'03'0E, 
            rgba16_snorm      = 0x10'00'04'0F, 
                                     
            rgb8_srgb         = 0x08'00'03'12, 
            rgba8_srgb        = 0x08'00'04'13, //Recommended for sRGB images
                                     
            r16_float         = 0x10'00'01'14, 
            rg16_float        = 0x10'00'02'15, 
            rgb16_float       = 0x10'00'03'16, 
            rgba16_float      = 0x10'00'04'17, 
                                     
            r32_float         = 0x20'00'01'18, 
            rg32_float        = 0x20'00'02'19, 
            rgb32_float       = 0x20'00'03'1A, 
            rgba32_float      = 0x20'00'04'1B, 
                                     
            d16_unorm         = 0x10'00'10'1C, 
            d24_unorm         = 0x18'00'10'1D, 
            d32_float         = 0x20'00'10'1E, 
                                
            d24_unorm_s8_uint = 0x18'08'30'1F, 
            d32_float_s8_uint = 0x20'08'30'20, 

            s8_uint           = 0x08'00'20'21, 
        };
        using      filter_e   = api::Texture::filter_e;
        using      wrapping_e = api::Texture::wrapping_e;
        enum class face_e
        {
            right, 
            left, 
            top, 
            bottom, 
            front, 
            back, 
        };
	};
}
