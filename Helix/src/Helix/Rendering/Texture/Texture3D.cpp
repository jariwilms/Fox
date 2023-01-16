#include "stdafx.hpp"

#include "Texture3D.hpp"

namespace hlx
{
	std::shared_ptr<Texture3D> Texture3D::create(Texture::Format format, Layout layout, const glm::uvec3& dimensions)
	{
		return {};
	}
	std::shared_ptr<Texture3D> Texture3D::create(Texture::Format format, Layout layout, const glm::uvec3& dimensions, const std::span<byte>& data)
	{
		return {};
	}
	std::shared_ptr<Texture3D> Texture3D::create(Texture::Format format, Layout layout, Wrapping wrappingS, Wrapping wrappingT, Wrapping wrappingR, Filter minFilter, Filter magFilter, const glm::uvec3& dimensions)
	{
		return {};
	}
	std::shared_ptr<Texture3D> Texture3D::create(Texture::Format format, Layout layout, Wrapping wrappingS, Wrapping wrappingT, Wrapping wrappingR, Filter minFilter, Filter magFilter, const glm::uvec3& dimensions, const std::span<byte>& data)
	{
		return {};
	}

	hlx::Texture::Wrapping Texture3D::wrapping_s() const
	{
		return m_wrappingS;
	}
	hlx::Texture::Wrapping Texture3D::wrapping_t() const
	{
		return m_wrappingT;
	}
	hlx::Texture::Wrapping Texture3D::wrapping_r() const
	{
		return m_wrappingR;
	}
	const glm::uvec3& Texture3D::dimensions() const
	{
		return m_dimensions;
	}

	Texture3D::Texture3D(Texture::Format format, Layout layout, const glm::uvec3& dimensions)
		: Texture{ format, layout } {}
	Texture3D::Texture3D(Texture::Format format, Layout layout, Wrapping wrappingS, Wrapping wrappingT, Wrapping wrappingR, Filter minFilter, Filter magFilter, const glm::uvec3& dimensions)
		: Texture{ format, layout, minFilter, magFilter }, m_wrappingS{ wrappingS }, m_wrappingT{ wrappingT }, m_wrappingR{ wrappingR }, m_dimensions { dimensions } {}
}
