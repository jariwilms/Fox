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
    OpenGLCubemapTexture::OpenGLCubemapTexture(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions, Components dataComponents, const std::type_info& dataType, std::span<std::span<const byte>, 6> data)
        : OpenGLCubemapTexture{ format, filter, wrapping, dimensions }
    {
        _copy(dataComponents, dataType, data);
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

    void OpenGLCubemapTexture::_copy(Components dataComponents, const std::type_info& typeInfo, std::span<std::span<const byte>, 6> data)
    {
        unsigned int index{};
        std::for_each(data.begin(), data.end(), [&](const auto& faceData) 
            { 
                _copy_face(static_cast<Face>(index), dataComponents, typeInfo, faceData); 
                ++index; 
            });
    }
    void OpenGLCubemapTexture::_copy_face(Face face, Components dataComponents, const std::type_info& dataType, std::span<const byte> data)
    {
        //const auto& area = m_dimensions.x * m_dimensions.y;
        //const auto& componentCount = dataComponents < Components::D ? static_cast<int>(dataComponents) : 1;
        //const auto& componentSize = OpenGL::type_enum(dataType.hash_code());
        throw std::logic_error{ "Method has not been implemented!" };

        _copy_face_range(face, m_dimensions, Vector2u{ 0u, 0u }, dataComponents, dataType, data);
    }
    void OpenGLCubemapTexture::_copy_face_range(Face face, const Vector2u& dimensions, const Vector2u& offset, Components dataComponents, const std::type_info& dataType, std::span<const byte> data)
    {
        if (data.empty()) return;

        const auto& format    = OpenGL::texture_format(dataComponents);
        const auto& type      = OpenGL::type_enum(dataType.hash_code());
        const auto& totalSize = offset + dimensions;
        if (glm::any(glm::greaterThan(m_dimensions, totalSize))) throw std::invalid_argument{ "The total size exceeds texture bounds!" };
        
        glTextureSubImage3D(m_internalId, 0, offset.x, offset.y, static_cast<GLint>(face), dimensions.x, dimensions.y, 1, format, type, data.data());
        if (m_mipLevels > 1) glGenerateTextureMipmap(m_internalId);
    }

    //void OpenGLCubemapTexture::copy(Format dataFormat, std::span<std::span<const byte>, 6> data, unsigned int mipLevel, bool generateMips)
    //{
    //    const auto size = m_dimensions.x * m_dimensions.y * static_cast<unsigned int>(dataFormat);
    //    const auto size_check = [size](std::span<const byte> subData)
    //    {
    //        return size == subData.size();
    //    };
    //    if (data.empty()) return;
    //    if (!std::all_of(data.begin(), data.end(), size_check)) throw std::invalid_argument{ "Data length does not match texture size!" };
    //    unsigned int zOffset{};
    //    const auto format = OpenGL::texture_format(dataFormat);
    //    for (const auto& subData : data)
    //    {
    //        glTextureSubImage3D(m_id, mipLevel, 0, 0, zOffset, m_dimensions.x, m_dimensions.y, 1, format, GL_UNSIGNED_BYTE, subData.data());
    //        ++zOffset;
    //    }
    //    if (generateMips) glGenerateTextureMipmap(m_id);
    //}
    //void OpenGLCubemapTexture::copy_range(const Vector2u& dimensions, const Vector2u& offset, Format DataFormat, std::span<std::span<const byte>, 6> data, unsigned int mipLevel, bool generateMips)
    //{
    //    throw std::runtime_error{ "The method or operation is not implemented." };
    //}
}
