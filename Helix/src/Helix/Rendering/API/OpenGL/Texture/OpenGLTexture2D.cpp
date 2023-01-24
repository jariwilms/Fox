#include "stdafx.hpp"

#include "OpenGLTexture2D.hpp"

namespace hlx
{
	OpenGLTexture2D::OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const glm::uvec2& dimensions)
		: Texture2D{ format, layout, dimensions }
	{
		m_internalFormat = OpenGL::texture_format(m_format);
		m_internalLayout = OpenGL::texture_layout(m_layout);

		glCreateTextures(m_internalTarget, 1, &m_id);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, OpenGL::texture_wrapping(m_wrappingS));
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, OpenGL::texture_wrapping(m_wrappingT));
		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, OpenGL::texture_min_filter(m_minFilter));
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, OpenGL::texture_mag_filter(m_magFilter));
		glTextureStorage2D(m_id, m_levels, m_internalLayout, m_dimensions.x, m_dimensions.y);
	}
	OpenGLTexture2D::OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const glm::uvec2& dimensions, const std::span<byte>& data)
		: OpenGLTexture2D{ format, layout, dimensions }
	{
		copy(dimensions, {}, data);
	}
	OpenGLTexture2D::OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const glm::uvec2& dimensions, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter, unsigned int levels)
		: Texture2D{ format, layout, dimensions, wrappingS, wrappingT, minFilter, magFilter, levels }
	{
		m_internalFormat = OpenGL::texture_format(m_format);
		m_internalLayout = OpenGL::texture_layout(m_layout);
		
		glCreateTextures(m_internalTarget, 1, &m_id);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, OpenGL::texture_wrapping(m_wrappingS));
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, OpenGL::texture_wrapping(m_wrappingT));
		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, OpenGL::texture_min_filter(m_minFilter));
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, OpenGL::texture_mag_filter(m_magFilter));
		glTextureStorage2D(m_id, m_levels, m_internalLayout, m_dimensions.x, m_dimensions.y);
	}
	OpenGLTexture2D::OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const glm::uvec2& dimensions, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter, unsigned int levels, const std::span<byte>& data)
		: OpenGLTexture2D{ format, layout, dimensions, wrappingS, wrappingT, minFilter, magFilter, levels }
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
		glTextureSubImage2D(m_id, 0, offset.x, offset.y, dimensions.x, dimensions.y, m_internalFormat, GL_UNSIGNED_BYTE, data.data());
		if (m_levels > 1) glGenerateTextureMipmap(m_id);
	}
}
