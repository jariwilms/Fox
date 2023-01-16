#include "stdafx.hpp"

#include "OpenGLTexture2D.hpp"

namespace hlx
{
	OpenGLTexture2D::OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const glm::uvec2& dimensions)
		: Texture2D{ format, layout, dimensions }
	{
		m_format = OpenGL::texture_format(format);
		m_internalFormat = OpenGL::texture_layout(m_layout);

		glCreateTextures(m_target, 1, &m_id);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, OpenGL::texture_wrapping(m_wrappingS));
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, OpenGL::texture_wrapping(m_wrappingT));
		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, OpenGL::texture_filter(m_minFilter));
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, OpenGL::texture_filter(m_magFilter));
		glTextureStorage2D(m_id, 1, m_internalFormat, m_dimensions.x, m_dimensions.y);
	}
	OpenGLTexture2D::OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const glm::uvec2& dimensions, const std::span<byte>& data)
		: OpenGLTexture2D{ format, layout, dimensions }
	{
		copy(dimensions, {}, data);
	}
	OpenGLTexture2D::OpenGLTexture2D(Texture::Format format, Texture::Layout layout, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::Filter minFilter, Texture::Filter magFilter, const glm::uvec2& dimensions)
		: Texture2D{ format, layout, wrappingS, wrappingT, minFilter, magFilter, dimensions }
	{
		m_format = OpenGL::texture_format(format);
		m_internalFormat = OpenGL::texture_layout(m_layout);

		glCreateTextures(m_target, 1, &m_id);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, OpenGL::texture_wrapping(m_wrappingS));
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, OpenGL::texture_wrapping(m_wrappingT));
		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, OpenGL::texture_filter(m_minFilter));
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, OpenGL::texture_filter(m_magFilter));
		glTextureStorage2D(m_id, 1, m_internalFormat, m_dimensions.x, m_dimensions.y);
	}
	OpenGLTexture2D::OpenGLTexture2D(Texture::Format format, Texture::Layout layout, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::Filter minFilter, Texture::Filter magFilter, const glm::uvec2& dimensions, const std::span<byte>& data)
		: OpenGLTexture2D{ format, layout, wrappingS, wrappingT, minFilter, magFilter, dimensions }
	{
		copy(dimensions, {}, data);
	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_id);
	}

	void OpenGLTexture2D::bind() const
	{
		bind(0);
	}
	void OpenGLTexture2D::bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, m_id);
	}
	void OpenGLTexture2D::unbind() const
	{

	}
	bool OpenGLTexture2D::is_bound() const
	{
		return false;
	}
	
	void OpenGLTexture2D::copy(const glm::uvec2& dimensions, const glm::uvec2& offset, const std::span<byte>& data) const
	{
		glTextureSubImage2D(m_id, 0, offset.x, offset.y, dimensions.x, dimensions.y, m_format, GL_UNSIGNED_BYTE, data.data());
		glGenerateTextureMipmap(m_id);
	}
}
