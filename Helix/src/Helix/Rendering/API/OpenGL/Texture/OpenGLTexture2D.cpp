#include "stdafx.hpp"

#include "OpenGLTexture2D.hpp"

namespace hlx
{
	OpenGLTexture2D::OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels)
		: Texture2D{ format, layout, dimensions, mipLevels }
	{
		m_internalFormat = OpenGL::texture_format(m_format);
		m_internalLayout = OpenGL::texture_layout(m_layout);

		glCreateTextures(m_internalTarget, 1, &m_id);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, OpenGL::texture_wrapping(m_wrappingS));
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, OpenGL::texture_wrapping(m_wrappingT));
		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, OpenGL::texture_min_filter(m_minFilter));
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, OpenGL::texture_mag_filter(m_magFilter));
		glTextureStorage2D(m_id, m_mipLevels, m_internalLayout, m_dimensions.x, m_dimensions.y);
	}
	OpenGLTexture2D::OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, std::span<const byte> data)
		: OpenGLTexture2D{ format, layout, dimensions, mipLevels }
	{
		copy(dimensions, {}, data);
	}
	OpenGLTexture2D::OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter)
		: Texture2D{ format, layout, dimensions, mipLevels, wrappingS, wrappingT, minFilter, magFilter }
	{
		m_internalFormat = OpenGL::texture_format(m_format);
		m_internalLayout = OpenGL::texture_layout(m_layout);
		
		glCreateTextures(m_internalTarget, 1, &m_id);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, OpenGL::texture_wrapping(m_wrappingS));
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, OpenGL::texture_wrapping(m_wrappingT));
		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, OpenGL::texture_min_filter(m_minFilter));
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, OpenGL::texture_mag_filter(m_magFilter));
		glTextureStorage2D(m_id, m_mipLevels, m_internalLayout, m_dimensions.x, m_dimensions.y);
	}
	OpenGLTexture2D::OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter, std::span<const byte> data)
		: OpenGLTexture2D{ format, layout, dimensions, mipLevels, wrappingS, wrappingT, minFilter, magFilter }
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
	bool OpenGLTexture2D::bound() const
	{
		return false;
	}
	
	void OpenGLTexture2D::copy(const Vector2u& dimensions, const Vector2u& offset, std::span<const byte> data) const
	{
		glTextureSubImage2D(m_id, 0, offset.x, offset.y, dimensions.x, dimensions.y, m_internalFormat, GL_UNSIGNED_BYTE, data.data());
		if (m_mipLevels > 1) glGenerateTextureMipmap(m_id);
	}
}
