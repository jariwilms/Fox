#pragma once

#include "stdafx.hpp"

#include "Texture.hpp"

namespace hlx
{
	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;

		virtual void copy(const Vector2u& dimensions, const Vector2u& offset, std::span<const byte> data) const = 0;

		Wrapping wrapping_s() const
		{
			return m_wrappingS;
		}
		Wrapping wrapping_t() const
		{
			return m_wrappingT;
		}
		const Vector2u& dimensions() const
		{
			return m_dimensions;
		}

	protected:
		Texture2D(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels)
            : Texture{ format, layout, mipLevels }, m_dimensions{ dimensions } {}
		Texture2D(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, Wrapping wrappingS, Wrapping wrappingT, MinFilter minFilter, MagFilter magFilter)
            : Texture{ format, layout, mipLevels, minFilter, magFilter }, m_dimensions{ dimensions }, m_wrappingS{ wrappingS }, m_wrappingT{ wrappingT } {}

		const Vector2u m_dimensions{};
        Wrapping       m_wrappingS{ Wrapping::ClampToEdge };
        Wrapping       m_wrappingT{ Wrapping::ClampToEdge };
	};
}
