#include "stdafx.hpp"

#include "OpenGLTexture2D.hpp"

namespace hlx
{
    OpenGLTexture2D::OpenGLTexture2D(Format format, Layout layout, const Vector2u& dimensions, unsigned int mipLevels, Wrapping wrappingS, Wrapping wrappingT, Filter filter, std::span<const byte> data)
		: Texture2D{ format, layout, dimensions, mipLevels, wrappingS, wrappingT, filter }
	{
		m_internalFormat = OpenGL::texture_format(m_format);
		m_internalLayout = OpenGL::texture_layout(m_layout);
		
		glCreateTextures(m_internalTarget, 1, &m_id);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, OpenGL::texture_wrapping(m_wrappingS));
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, OpenGL::texture_wrapping(m_wrappingT));
        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, OpenGL::texture_min_filter(m_filter));
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, OpenGL::texture_mag_filter(m_filter));
		glTextureStorage2D(m_id, m_mipLevels, m_internalLayout, m_dimensions.x, m_dimensions.y);

		copy(data);
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
        throw std::logic_error("The method or operation is not implemented.");
	}
	bool OpenGLTexture2D::bound() const
	{
        throw std::logic_error("The method or operation is not implemented.");
	}
	
	void OpenGLTexture2D::copy(std::span<const byte> data, unsigned int mipLevel, bool generateMips)
	{
		const auto size = m_dimensions.x* m_dimensions.y * 4;

        if (data.empty()) return;
        if (size != data.size()) throw std::invalid_argument{ "Data length does not match texture size!" };

		glTextureSubImage2D(m_id, mipLevel, 0, 0, m_dimensions.x, m_dimensions.y, m_internalFormat, GL_UNSIGNED_BYTE, data.data());
		if (generateMips) glGenerateTextureMipmap(m_id);
	}
	void OpenGLTexture2D::copy_range(const Vector2u& dimensions, const Vector2u& offset, std::span<const byte> data, unsigned int mipLevel, bool generateMips)
	{
		const auto size = m_dimensions.x * m_dimensions.y * 4;

        if (data.empty()) return;
		if (offset.x + dimensions.x > m_dimensions.x || offset.y + dimensions.y > m_dimensions.y) throw std::out_of_range{ "Image dimensions are not within texture bounds!" };

		glTextureSubImage2D(m_id, mipLevel, offset.x, offset.y, dimensions.x, dimensions.y, m_internalFormat, GL_UNSIGNED_BYTE, data.data());
		if (generateMips) glGenerateTextureMipmap(m_id);
	}
}
