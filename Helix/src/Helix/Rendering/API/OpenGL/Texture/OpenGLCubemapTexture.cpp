#include "stdafx.hpp"

#include "OpenGLCubemapTexture.hpp"

namespace hlx
{
    OpenGLCubemapTexture::OpenGLCubemapTexture(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions)
        : CubemapTexture{ format, filter, wrapping, dimensions }
    {
        m_id = OpenGL::create_texture(GL_TEXTURE_CUBE_MAP);

        const auto& internalFormat    = OpenGL::texture_format(m_format);
        const auto& internalMinFilter = OpenGL::texture_min_filter(m_filter);
        const auto& internalMagFilter = OpenGL::texture_mag_filter(m_filter);
        const auto& internalWrappping = OpenGL::texture_wrapping(m_wrapping);

        OpenGL::texture_parameter(m_id, GL_TEXTURE_MIN_FILTER, internalMinFilter);
        OpenGL::texture_parameter(m_id, GL_TEXTURE_MAG_FILTER, internalMagFilter);
        OpenGL::texture_parameter(m_id, GL_TEXTURE_WRAP_S, internalWrappping);
        OpenGL::texture_parameter(m_id, GL_TEXTURE_WRAP_T, internalWrappping);
        OpenGL::texture_parameter(m_id, GL_TEXTURE_WRAP_R, internalWrappping);
        OpenGL::texture_storage_2d(m_id, internalFormat, m_dimensions, m_mipLevels);
    }
    OpenGLCubemapTexture::OpenGLCubemapTexture(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions, Components components, std::span<std::span<const byte>, 6> data)
        : OpenGLCubemapTexture{ format, filter, wrapping, dimensions }
    {
        copy(components, data);
    }
    OpenGLCubemapTexture::~OpenGLCubemapTexture()
    {
        OpenGL::delete_texture(m_id);
    }

    void OpenGLCubemapTexture::bind(unsigned int slot) const
    {
        OpenGL::bind_texture(m_id, slot);
    }

    void OpenGLCubemapTexture::copy(Components components, std::span<std::span<const byte>, 6> data)
    {
        unsigned int index{};
        std::for_each(data.begin(), data.end(), [&](const auto& faceData) 
            { 
                copy_face(static_cast<Face>(index), components, faceData); 
                ++index; 
            });
    }
    void OpenGLCubemapTexture::copy_face(Face face, Components components, std::span<const byte> data)
    {
        copy_face_range(face, m_dimensions, Vector2u{ 0u, 0u }, components, data);
    }
    void OpenGLCubemapTexture::copy_face_range(Face face, const Vector2u& dimensions, const Vector2u& offset, Components components, std::span<const byte> data)
    {
        if (data.empty()) return;
        if (glm::any(glm::greaterThan(m_dimensions, offset + dimensions))) throw std::invalid_argument{ "The data size exceeds texture bounds!" };

        const auto& format = OpenGL::texture_format(components);
        OpenGL::texture_sub_image_3d(m_id, format, Vector3u{ dimensions, 1u }, Vector3u{ offset, static_cast<GLint>(face) }, 0, data.data());
        if (m_mipLevels > 1) OpenGL::generate_texture_mipmap(m_id);
    }
}
