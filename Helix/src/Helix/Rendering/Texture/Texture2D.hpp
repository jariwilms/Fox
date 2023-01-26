#pragma once

#include "stdafx.hpp"

#include "Texture.hpp"

namespace hlx
{
	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;

		virtual void copy(const glm::uvec2& dimensions, const glm::uvec2& offset, const std::span<byte>& data) const = 0;

		Wrapping wrapping_s() const
		{
			return m_wrappingS;
		}
		Wrapping wrapping_t() const
		{
			return m_wrappingT;
		}
		const glm::uvec2& dimensions() const
		{
			return m_dimensions;
		}

	protected:
		Texture2D(Texture::Format format, Layout layout, const glm::uvec2& dimensions, unsigned int mipLevels)
            : Texture{ format, layout, mipLevels }, m_dimensions{ dimensions } {}
		Texture2D(Texture::Format format, Layout layout, const glm::uvec2& dimensions, unsigned int mipLevels, Wrapping wrappingS, Wrapping wrappingT, MinFilter minFilter, MagFilter magFilter)
            : Texture{ format, layout, mipLevels, minFilter, magFilter }, m_dimensions{ dimensions }, m_wrappingS{ wrappingS }, m_wrappingT{ wrappingT } {}

		const glm::uvec2 m_dimensions{};
        Wrapping         m_wrappingS{ Wrapping::ClampToEdge };
        Wrapping         m_wrappingT{ Wrapping::ClampToEdge };
	};
}
