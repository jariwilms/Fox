#include "stdafx.hpp"

#include "OpenGLTexture2D.hpp"

namespace hlx
{
    OpenGLTexture2D::OpenGLTexture2D(Format format, ColorDepth colorDepth, const Vector2u& dimensions, Filter filter, Wrapping wrappingS, Wrapping wrappingT, unsigned int mipLevels, bool sRGB)
		: Texture2D{ format, colorDepth, dimensions, filter, wrappingS, wrappingT, mipLevels, sRGB }
    {
        m_internalFormat = OpenGL::texture_format(m_format);
        m_internalLayout = OpenGL::texture_layout(m_format, m_colorDepth, m_sRGB);

        glCreateTextures(m_internalTarget, 1, &m_id);
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, OpenGL::texture_wrapping(m_wrappingS));
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, OpenGL::texture_wrapping(m_wrappingT));
        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, OpenGL::texture_min_filter(m_filter));
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, OpenGL::texture_mag_filter(m_filter));
        glTextureStorage2D(m_id, m_mipLevels, m_internalLayout, m_dimensions.x, m_dimensions.y);
    }
    OpenGLTexture2D::OpenGLTexture2D(Format format, ColorDepth colorDepth, const Vector2u& dimensions, Filter filter, Wrapping wrappingS, Wrapping wrappingT, unsigned int mipLevels, bool sRGB, Format dataFormat, std::span<const byte> data)
        : OpenGLTexture2D{ format, colorDepth, dimensions, filter, wrappingS, wrappingT, mipLevels, sRGB }
    {
        copy(dataFormat, data);
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
		const auto& pair = s_boundTextureIds.try_emplace(slot, 0);
		if (pair.first->second == m_id) return;

		glBindTextureUnit(slot, m_id);
		s_boundTextureIds.at(slot) = m_id;
	}
	void OpenGLTexture2D::unbind() const
	{
        throw std::logic_error("The method or operation is not implemented.");
	}
	bool OpenGLTexture2D::is_bound() const
	{
        throw std::logic_error("The method or operation is not implemented.");
	}
	
	void OpenGLTexture2D::copy(Format dataFormat, std::span<const byte> data, unsigned int mipLevel, bool generateMips)
	{
        if (data.empty()) return;
		if (const auto size{ m_dimensions.x * m_dimensions.y * static_cast<unsigned int>(dataFormat) }; size != data.size()) throw std::invalid_argument{ "Data length does not match texture size!" };

		const auto format = OpenGL::texture_format(dataFormat);
		glTextureSubImage2D(m_id, mipLevel, 0, 0, m_dimensions.x, m_dimensions.y, format, GL_UNSIGNED_BYTE, data.data());
		if (generateMips) glGenerateTextureMipmap(m_id);
	}
	void OpenGLTexture2D::copy_range(const Vector2u& dimensions, const Vector2u& offset, Format dataFormat, std::span<const byte> data, unsigned int mipLevel, bool generateMips)
	{
        if (data.empty()) return;
        if (const auto size = m_dimensions.x * m_dimensions.y * static_cast<unsigned int>(dataFormat); size != data.size()) throw std::invalid_argument{ "Data length does not match texture size!" };
		if (const auto totalSize = Vector2u{ offset.x + dimensions.x, offset.y + dimensions.y }; totalSize.x > m_dimensions.x || totalSize.y > m_dimensions.y) throw std::out_of_range{ "Image dimensions are not within texture bounds!" };
		
        const auto format = OpenGL::texture_format(dataFormat);
		glTextureSubImage2D(m_id, mipLevel, offset.x, offset.y, dimensions.x, dimensions.y, format, GL_UNSIGNED_BYTE, data.data());
		if (generateMips) glGenerateTextureMipmap(m_id);
	}
}
