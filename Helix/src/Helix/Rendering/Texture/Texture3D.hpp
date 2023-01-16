#pragma once

#include "stdafx.hpp"

#include "Texture.hpp"

namespace hlx
{
	class Texture3D : public Texture
	{
	public:
		virtual ~Texture3D() = default;

		static std::shared_ptr<Texture3D> create(Texture::Format format, Layout layout, const glm::uvec3& dimensions);
		static std::shared_ptr<Texture3D> create(Texture::Format format, Layout layout, const glm::uvec3& dimensions, const std::span<byte>& data);
		static std::shared_ptr<Texture3D> create(Texture::Format format, Layout layout, Wrapping wrappingS, Wrapping wrappingT, Wrapping wrappingR, Filter minFilter, Filter magFilter, const glm::uvec3& dimensions);
		static std::shared_ptr<Texture3D> create(Texture::Format format, Layout layout, Wrapping wrappingS, Wrapping wrappingT, Wrapping wrappingR, Filter minFilter, Filter magFilter, const glm::uvec3& dimensions, const std::span<byte>& data);

		virtual void copy(const glm::uvec3& dimensions, const glm::uvec3& offset, const std::span<byte>& data) const = 0;

		Wrapping wrapping_s() const;
		Wrapping wrapping_t() const;
		Wrapping wrapping_r() const;
		const glm::uvec3& dimensions() const;

	protected:
		Texture3D(Texture::Format format, Layout layout, const glm::uvec3& dimensions);
		Texture3D(Texture::Format format, Layout layout, Wrapping wrappingS, Wrapping wrappingT, Wrapping wrappingR, Filter minFilter, Filter magFilter, const glm::uvec3& dimensions);

		Wrapping           m_wrappingS{ Wrapping::ClampToEdge };
		Wrapping           m_wrappingT{ Wrapping::ClampToEdge };
		Wrapping           m_wrappingR{ Wrapping::ClampToEdge };
		const glm::uvec3   m_dimensions{};
	};
}
