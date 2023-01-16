#include "stdafx.hpp"

#include "Texture2D.hpp"

#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2D.hpp"

namespace hlx
{
	std::shared_ptr<Texture2D> Texture2D::create(Texture::Format format, Layout layout, const glm::uvec2& dimensions)
	{
		return std::make_shared<OpenGLTexture2D>(format, layout, dimensions);
	}
	std::shared_ptr<Texture2D> Texture2D::create(Texture::Format format, Layout layout, const glm::uvec2& dimensions, const std::span<byte>& data)
	{
		return std::make_shared<OpenGLTexture2D>(format, layout, dimensions, data);
	}
	std::shared_ptr<Texture2D> Texture2D::create(Texture::Format format, Layout layout, Wrapping wrappingS, Wrapping wrappingT, Filter minFilter, Filter magFilter, const glm::uvec2& dimensions)
	{
		return std::make_shared<OpenGLTexture2D>(format, layout, wrappingS, wrappingT, minFilter, magFilter, dimensions);
	}
	std::shared_ptr<Texture2D> Texture2D::create(Texture::Format format, Layout layout, Wrapping wrappingS, Wrapping wrappingT, Filter minFilter, Filter magFilter, const glm::uvec2& dimensions, const std::span<byte>& data)
	{
		return std::make_shared<OpenGLTexture2D>(format, layout, wrappingS, wrappingT, minFilter, magFilter, dimensions, data);
	}

	Texture::Wrapping Texture2D::wrapping_s() const
	{
		return m_wrappingS;
	}
	Texture::Wrapping Texture2D::wrapping_t() const
	{
		return m_wrappingT;
	}
	const glm::uvec2& Texture2D::dimensions() const
	{
		return m_dimensions;
	}

	Texture2D::Texture2D(Texture::Format format, Layout layout, const glm::uvec2& dimensions)
		: Texture{ format, layout }, m_dimensions{ dimensions } {}
	Texture2D::Texture2D(Texture::Format format, Layout layout, Wrapping wrappingS, Wrapping wrappingT, Filter minFilter, Filter magFilter, const glm::uvec2& dimensions)
		: Texture{ format, layout, minFilter, magFilter }, m_wrappingS{ wrappingS }, m_wrappingT{ wrappingT }, m_dimensions{ dimensions } {}
}
