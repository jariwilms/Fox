#include "stdafx.hpp"

#include "OpenGLCubemapTexture.hpp"

namespace hlx
{
    OpenGLCubemapTexture::OpenGLCubemapTexture(Format format, ColorDepth colorDepth, const Vector2u& dimensions, Filter filter, Wrapping wrappingR, Wrapping wrappingS, Wrapping wrappingT, unsigned int mipLevels, bool sRGB)
        : CubemapTexture{ format, colorDepth, dimensions, filter, wrappingR, wrappingS, wrappingT, mipLevels, sRGB }
    {
        m_internalFormat = OpenGL::texture_format(m_format);
        m_internalLayout = OpenGL::texture_layout(m_format, m_colorDepth);

        glCreateTextures(m_internalTarget, 1, &m_id);
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, OpenGL::texture_wrapping(m_wrappingS));
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, OpenGL::texture_wrapping(m_wrappingT));
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_R, OpenGL::texture_wrapping(m_wrappingR));
        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, OpenGL::texture_min_filter(m_filter));
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, OpenGL::texture_mag_filter(m_filter));
        glTextureStorage2D(m_id, m_mipLevels, m_internalLayout, m_dimensions.x, m_dimensions.y);
    }
    OpenGLCubemapTexture::OpenGLCubemapTexture(Format format, ColorDepth colorDepth, const Vector2u& dimensions, Filter filter, Wrapping wrappingR, Wrapping wrappingS, Wrapping wrappingT, unsigned int mipLevels, bool sRGB, Format dataFormat, const std::array<std::span<const byte>, 6>& data)
        : OpenGLCubemapTexture{ format, colorDepth, dimensions, filter, wrappingR, wrappingS, wrappingT, mipLevels, sRGB }
    {
        copy(format, data);
    }
    OpenGLCubemapTexture::~OpenGLCubemapTexture()
    {
        glDeleteTextures(1, &m_id);
    }

    void OpenGLCubemapTexture::bind() const
    {
        bind(0);
    }
    void OpenGLCubemapTexture::bind(unsigned int slot) const
    {
        glBindTextureUnit(slot, m_id);
    }
    void OpenGLCubemapTexture::unbind() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }
    bool OpenGLCubemapTexture::bound() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void OpenGLCubemapTexture::copy(Format dataFormat, const std::array<std::span<const byte>, 6>& data, unsigned int mipLevel, bool generateMips)
    {
        const auto size = m_dimensions.x * m_dimensions.y * static_cast<unsigned int>(dataFormat);
        const auto size_check = [size](std::span<const byte> subData)
        {
            return size == subData.size();
        };

        if (data.empty()) return;
        if (!std::all_of(data.begin(), data.end(), size_check)) throw std::invalid_argument{ "Data length does not match texture size!" };

        unsigned int zOffset{};
        const auto format = OpenGL::texture_format(dataFormat);
        for (const auto& subData : data)
        {
            glTextureSubImage3D(m_id, mipLevel, 0, 0, zOffset, m_dimensions.x, m_dimensions.y, 1, format, GL_UNSIGNED_BYTE, subData.data());
            ++zOffset;
        }
        if (generateMips) glGenerateTextureMipmap(m_id);
    }
    void OpenGLCubemapTexture::copy_range(const Vector2u dimensions, const Vector2u& offset, Format DataFormat, const std::array<std::span<const byte>, 6>& data, unsigned int mipLevel, bool generateMips)
    {
        throw std::runtime_error{ "The method or operation is not implemented." };
    }
}
