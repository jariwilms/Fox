#pragma once

namespace fox::gfx::api
{
	class RenderBuffer
	{
	public:
		enum class Format
		{
            R8_UNORM, 
            RG8_UNORM, 
            RGB8_UNORM, 
            RGBA8_UNORM, 

            RGBA8_SRGB, 

            D16_UNORM, 
            D24_UNORM, 
            D32_FLOAT, 

            D24_UNORM_S8_UINT, 
            D32_FLOAT_S8_UINT, 

            S8_UINT, 
		};
	};
}
