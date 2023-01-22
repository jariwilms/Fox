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
		//TODO: add mipmap filtering options => texture filter + mipmap filter options
	protected:
		Texture2D(Texture::Format format, Layout layout, const glm::uvec2& dimensions)
            : Texture{ format, layout }, m_dimensions{ dimensions } {}
		Texture2D(Texture::Format format, Layout layout, Wrapping wrappingS, Wrapping wrappingT, Filter minFilter, Filter magFilter, const glm::uvec2& dimensions)
            : Texture{ format, layout, minFilter, magFilter, 1 }, m_wrappingS{ wrappingS }, m_wrappingT{ wrappingT }, m_dimensions{ dimensions } {}

		Wrapping           m_wrappingS{ Wrapping::ClampToEdge };
		Wrapping           m_wrappingT{ Wrapping::ClampToEdge };
		const glm::uvec2   m_dimensions{};
	};
}
