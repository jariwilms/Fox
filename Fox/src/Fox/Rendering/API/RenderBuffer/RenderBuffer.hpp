#pragma once

#include "stdafx.hpp"

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

        RenderBuffer(RenderBuffer&&) = default;

        Format format() const
        {
            return m_format;
        }

        RenderBuffer& operator=(RenderBuffer&&) noexcept = default;

    protected:
        RenderBuffer(Format format)
            : m_format{ format } {}

        Format m_format;
	};
}
