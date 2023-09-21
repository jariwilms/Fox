#include "stdafx.hpp"

#include "OpenGLTexture2D.hpp"

namespace hlx
{
    OpenGLTexture2D::OpenGLTexture2D(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions)
		: Texture2D{ format, filter, wrapping, dimensions }
    {
		m_internalId        = OpenGL::create_texture(GL_TEXTURE_2D);
        m_internalFormat    = OpenGL::texture_format(m_format);
		m_internalMinFilter = OpenGL::texture_min_filter(m_filter);
		m_internalMagFilter = OpenGL::texture_mag_filter(m_filter);
		m_internalWrapping  = OpenGL::texture_wrapping(m_wrapping);

        OpenGL::texture_parameter(m_internalId, GL_TEXTURE_MIN_FILTER, m_internalMinFilter);
        OpenGL::texture_parameter(m_internalId, GL_TEXTURE_MAG_FILTER, m_internalMagFilter);
        OpenGL::texture_parameter(m_internalId, GL_TEXTURE_WRAP_S, m_internalWrapping);
		OpenGL::texture_parameter(m_internalId, GL_TEXTURE_WRAP_T, m_internalWrapping);
		OpenGL::texture_storage_2d(m_internalId, m_internalFormat, m_dimensions, m_mipLevels);
    }
    OpenGLTexture2D::OpenGLTexture2D(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions, Components components, std::span<const byte> data)
        : OpenGLTexture2D{ format, filter, wrapping, dimensions }
    {
        copy(components, data);
    }
    OpenGLTexture2D::~OpenGLTexture2D()
	{
		OpenGL::delete_texture(m_internalId);
	}

	void OpenGLTexture2D::bind(unsigned int slot) const
    {
		OpenGL::bind_texture(m_internalId, slot);
	}
	
	void OpenGLTexture2D::copy(Components components, std::span<const byte> data)
	{
		copy_range(m_dimensions, Vector2u{ 0u, 0u }, components, data);
	}
	void OpenGLTexture2D::copy_range(const Vector2u& dimensions, const Vector2u& offset, Components components, std::span<const byte> data)
	{
        if (data.empty()) return;
		if (glm::any(glm::greaterThan(m_dimensions, offset + dimensions))) throw std::invalid_argument{ "The data size exceeds texture bounds!" };

        const auto& format = OpenGL::texture_format(components);
		OpenGL::texture_sub_image_2d(m_internalId, format, dimensions, offset, 0, data.data());
		if (m_mipLevels > 1) OpenGL::generate_texture_mipmap(m_internalId);
	}
}
