#include "stdafx.hpp"

#include "OpenGLTexture2D.hpp"

namespace hlx
{
    OpenGLTexture2D::OpenGLTexture2D(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions)
		: Texture2D{ format, filter, wrapping, dimensions }
    {
		m_id = OpenGL::create_texture(GL_TEXTURE_2D);

        const auto& internalFormat    = OpenGL::texture_format(m_format);
		const auto& internalMinFilter = OpenGL::texture_min_filter(m_filter);
		const auto& internalMagFilter = OpenGL::texture_mag_filter(m_filter);
		const auto& internalWrapping  = OpenGL::texture_wrapping(m_wrapping);

        OpenGL::texture_parameter(m_id, GL_TEXTURE_MIN_FILTER, internalMinFilter);
        OpenGL::texture_parameter(m_id, GL_TEXTURE_MAG_FILTER, internalMagFilter);
        OpenGL::texture_parameter(m_id, GL_TEXTURE_WRAP_S, internalWrapping);
		OpenGL::texture_parameter(m_id, GL_TEXTURE_WRAP_T, internalWrapping);
		OpenGL::texture_storage_2d(m_id, internalFormat, m_dimensions, m_mipLevels);
    }
    OpenGLTexture2D::OpenGLTexture2D(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions, Components components, std::span<const byte> data)
        : OpenGLTexture2D{ format, filter, wrapping, dimensions }
    {
        copy(components, data);
    }
    OpenGLTexture2D::~OpenGLTexture2D()
	{
		OpenGL::delete_texture(m_id);
	}

	void OpenGLTexture2D::bind(unsigned int slot) const
    {
		OpenGL::bind_texture(m_id, slot);
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
		OpenGL::texture_sub_image_2d(m_id, format, dimensions, offset, 0, data.data());
		if (m_mipLevels > 1u) OpenGL::generate_texture_mipmap(m_id);
	}
}
