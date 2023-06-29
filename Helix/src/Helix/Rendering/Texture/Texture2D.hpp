#pragma once

#include "stdafx.hpp"

#include "Texture.hpp"

namespace hlx
{
	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;

		virtual void copy(Format dataFormat, std::span<const byte> data, unsigned int mipLevel = 0, bool generateMips = true) = 0;
		virtual void copy_range(const Vector2u& dimensions, const Vector2u& offset, Format dataFormat, std::span<const byte> data, unsigned int mipLevel = 0, bool generateMips = true) = 0;

		const Vector2u& dimensions() const
		{
			return m_dimensions;
		}
		Wrapping wrapping_s() const
		{
			return m_wrappingS;
		}
		Wrapping wrapping_t() const
		{
			return m_wrappingT;
		}

	protected:
		Texture2D(Format format, ColorDepth colorDepth, const Vector2u& dimensions, Filter filter, Wrapping wrappingS, Wrapping wrappingT, unsigned int mipLevels, bool sRGB)
            : Texture{ format, colorDepth, filter, mipLevels, sRGB }, m_dimensions{ dimensions }, m_wrappingS{ wrappingS }, m_wrappingT{ wrappingT } {}

		const Vector2u m_dimensions{};
        const Wrapping m_wrappingS{};
        const Wrapping m_wrappingT{};
	};
}
