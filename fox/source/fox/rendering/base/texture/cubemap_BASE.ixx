export module fox.rendering.base.cubemap;

import fox.rendering.base.texture;

export namespace fox::gfx::api
{
	class Cubemap
	{
	public:
        enum class Format
        {
            //UNORM => stored as unsigned integer, sampled             as floating point   in range [        0,         1]
            //SNORM => stored as   signed integer, sampled             as floating point   in range [       -1,         1]
            //SRGB  => stored as unsigned integer, sampled nonlinearly as floating point   in range [        0,  UINT_MAX]
            //UINT  => stored as unsigned integer, sampled             as unsigned integer in range [        0,  UINT_MAX]
            //FLOAT => stored as   floating point, sampled             as floating point   in range [FLOAT_MIN, FLOAT_MAX]

            //Format: 0x|First component size|'|Second component size|'|No. components|'|Primary key|

            R8_UNORM          = 0x08'00'01'00, 
            RG8_UNORM         = 0x08'00'02'01, 
            RGB8_UNORM        = 0x08'00'03'02, 
            RGBA8_UNORM       = 0x08'00'04'03, //Recommended for color images
                                     
            R16_UNORM         = 0x10'00'01'04, 
            RG16_UNORM        = 0x10'00'02'05, 
            RGB16_UNORM       = 0x10'00'03'06, 
            RGBA16_UNORM      = 0x10'00'04'07, 
                                     
            R8_SNORM          = 0x08'00'01'08, 
            RG8_SNORM         = 0x08'00'02'09, 
            RGB8_SNORM        = 0x08'00'03'0A, 
            RGBA8_SNORM       = 0x08'00'04'0B, //Recommended for normal maps
                                     
            R16_SNORM         = 0x10'00'01'0C, 
            RG16_SNORM        = 0x10'00'02'0D, 
            RGB16_SNORM       = 0x10'00'03'0E, 
            RGBA16_SNORM      = 0x10'00'04'0F, 
                                     
            RGB8_SRGB         = 0x08'00'03'12, 
            RGBA8_SRGB        = 0x08'00'04'13, //Recommended for sRGB images
                                     
            R16_FLOAT         = 0x10'00'01'14, 
            RG16_FLOAT        = 0x10'00'02'15, 
            RGB16_FLOAT       = 0x10'00'03'16, 
            RGBA16_FLOAT      = 0x10'00'04'17, 
                                     
            R32_FLOAT         = 0x20'00'01'18, 
            RG32_FLOAT        = 0x20'00'02'19, 
            RGB32_FLOAT       = 0x20'00'03'1A, 
            RGBA32_FLOAT      = 0x20'00'04'1B, 
                                     
            D16_UNORM         = 0x10'00'10'1C, 
            D24_UNORM         = 0x18'00'10'1D, 
            D32_FLOAT         = 0x20'00'10'1E, 
                                
            D24_UNORM_S8_UINT = 0x18'08'30'1F, 
            D32_FLOAT_S8_UINT = 0x20'08'30'20, 

            S8_UINT           = 0x08'00'20'21, 
        };
        using      Filter   = api::Texture::Filter;
        using      Wrapping = api::Texture::Wrapping;
        enum class Face
        {
            Right, 
            Left, 
            Top, 
            Bottom, 
            Front, 
            Back, 
        };
	};
}
