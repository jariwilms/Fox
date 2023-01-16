#pragma once

#include "stdafx.hpp"

#include "Texture.hpp"

namespace hlx
{
	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;

		static std::shared_ptr<Texture2D> create(Texture::Format format, Layout layout, const glm::uvec2& dimensions);
		static std::shared_ptr<Texture2D> create(Texture::Format format, Layout layout, const glm::uvec2& dimensions, const std::span<byte>& data);
		static std::shared_ptr<Texture2D> create(Texture::Format format, Layout layout, Wrapping wrappingS, Wrapping wrappingT, Filter minFilter, Filter magFilter, const glm::uvec2& dimensions);
		static std::shared_ptr<Texture2D> create(Texture::Format format, Layout layout, Wrapping wrappingS, Wrapping wrappingT, Filter minFilter, Filter magFilter, const glm::uvec2& dimensions, const std::span<byte>& data);

		virtual void copy(const glm::uvec2& dimensions, const glm::uvec2& offset, const std::span<byte>& data) const = 0;

		Wrapping wrapping_s() const;
		Wrapping wrapping_t() const;
		const glm::uvec2& dimensions() const;

	protected:
		Texture2D(Texture::Format format, Layout layout, const glm::uvec2& dimensions);
		Texture2D(Texture::Format format, Layout layout, Wrapping wrappingS, Wrapping wrappingT, Filter minFilter, Filter magFilter, const glm::uvec2& dimensions);

		Wrapping           m_wrappingS{ Wrapping::ClampToEdge };
		Wrapping           m_wrappingT{ Wrapping::ClampToEdge };
		const glm::uvec2   m_dimensions{};
	};
}
