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
            D32_SFLOAT, 

            D24_UNORM_S8_UINT, 
            D32_SFLOAT_S8_UINT, 

            S8_UINT, 
		};

        Format format() const
        {
            return m_format;
        }

    protected:
        RenderBuffer(Format format)
            : m_format{ format } {}
        RenderBuffer(RenderBuffer&& other) = default;
        ~RenderBuffer() = default;

        RenderBuffer& operator=(RenderBuffer&& other) = default;

        Format m_format;
	};
}
