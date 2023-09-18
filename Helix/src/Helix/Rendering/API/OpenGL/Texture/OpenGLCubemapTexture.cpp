#include "stdafx.hpp"

#include "OpenGLCubemapTexture.hpp"

namespace hlx
{
    OpenGLCubemapTexture::OpenGLCubemapTexture(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions)
        : CubemapTexture{ format, filter, wrapping, dimensions }
    {
        m_internalTarget    = GL_TEXTURE_CUBE_MAP;
        m_internalFormat    = OpenGL::texture_format(m_format);
        m_internalMinFilter = OpenGL::texture_min_filter(m_filter);
        m_internalMagFilter = OpenGL::texture_mag_filter(m_filter);
        m_internalWrapping  = OpenGL::texture_wrapping(m_wrapping);

        glCreateTextures(m_internalTarget, 1, &m_internalId);
        glTextureParameteri(m_internalId, GL_TEXTURE_MIN_FILTER, m_internalMinFilter);
        glTextureParameteri(m_internalId, GL_TEXTURE_MAG_FILTER, m_internalMagFilter);
        glTextureParameteri(m_internalId, GL_TEXTURE_WRAP_S, m_internalWrapping);
        glTextureParameteri(m_internalId, GL_TEXTURE_WRAP_T, m_internalWrapping);
        glTextureParameteri(m_internalId, GL_TEXTURE_WRAP_R, m_internalWrapping);
        glTextureStorage2D(m_internalId, m_mipLevels, m_internalFormat, m_dimensions.x, m_dimensions.y);
    }
    OpenGLCubemapTexture::OpenGLCubemapTexture(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions, Components components, std::span<std::span<const byte>, 6> data)
        : OpenGLCubemapTexture{ format, filter, wrapping, dimensions }
    {
        copy(components, data);
    }
    OpenGLCubemapTexture::~OpenGLCubemapTexture()
    {
        glDeleteTextures(1, &m_internalId);
    }

    void OpenGLCubemapTexture::bind(unsigned int slot) const
    {
        const auto& pair = s_slotToIdMap.try_emplace(slot, 0);
        if (pair.first->second == m_internalId) return;

        glBindTextureUnit(slot, m_internalId);
        s_slotToIdMap.at(slot) = m_internalId;
        s_idToSlotMap.insert_or_assign(m_internalId, slot);
    }
    void OpenGLCubemapTexture::unbind() const
    {
        const auto& it = s_idToSlotMap.find(m_internalId);
        if (it == s_idToSlotMap.end()) return;

        const auto& slot = it->first;
        glBindTextureUnit(slot, 0);
        s_slotToIdMap.at(slot) = 0;
        s_idToSlotMap.at(m_internalId) = 0;
    }
    bool OpenGLCubemapTexture::is_bound() const
    {
        const auto& it = s_idToSlotMap.find(m_internalId);
        if (it == s_idToSlotMap.end()) return false;

        return it->first != 0;
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
        glTextureSubImage3D(m_internalId, 0, offset.x, offset.y, static_cast<GLint>(face), dimensions.x, dimensions.y, 1, format, GL_UNSIGNED_BYTE, data.data());
        if (m_mipLevels > 1) glGenerateTextureMipmap(m_internalId);
    }
}
