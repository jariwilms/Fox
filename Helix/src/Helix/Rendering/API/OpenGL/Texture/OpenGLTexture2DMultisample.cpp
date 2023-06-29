#include "stdafx.hpp"

#include "OpenGLTexture2DMultisample.hpp"

namespace hlx
{
    OpenGLTexture2DMultisample::OpenGLTexture2DMultisample(Format format, ColorDepth colorDepth, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, bool sRGB)
        : Texture2DMultisample{ format, colorDepth, dimensions, mipLevels, samples, sRGB }
    {
        m_internalFormat = OpenGL::texture_format(m_format);
        m_internalLayout = OpenGL::texture_layout(m_format, m_colorDepth, m_sRGB);

        glCreateTextures(m_internalTarget, 1, &m_id);
        glTextureStorage2DMultisample(m_id, m_samples, m_internalLayout, m_dimensions.x, m_dimensions.y, GL_TRUE);
    }
    OpenGLTexture2DMultisample::OpenGLTexture2DMultisample(Format format, ColorDepth colorDepth, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, bool sRGB, Format dataFormat, std::span<const byte> data)
        : OpenGLTexture2DMultisample{format, colorDepth, dimensions, mipLevels, samples, sRGB }
    {
        copy(m_format, data);
    }
    OpenGLTexture2DMultisample::~OpenGLTexture2DMultisample()
    {
        glDeleteTextures(1, &m_id);
    }

    void OpenGLTexture2DMultisample::bind() const
    {
        bind(0);
    }
    void OpenGLTexture2DMultisample::bind(unsigned int slot) const
    {
        glBindTextureUnit(slot, m_id);
    }
    void OpenGLTexture2DMultisample::unbind() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }
    bool OpenGLTexture2DMultisample::bound() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void OpenGLTexture2DMultisample::copy(Format dataFormat, std::span<const byte> data, unsigned int mipLevel, bool generateMips)
    {
        if (data.empty()) return;
        if (const auto size = m_dimensions.x * m_dimensions.y * static_cast<unsigned int>(dataFormat); size != data.size()) throw std::invalid_argument{ "Data length does not match texture size!" };

        const auto format = OpenGL::texture_format(dataFormat);
        glTextureSubImage2D(m_id, mipLevel, 0, 0, m_dimensions.x, m_dimensions.y, format, GL_UNSIGNED_BYTE, data.data());
        if (generateMips) glGenerateTextureMipmap(m_id);
    }
    void OpenGLTexture2DMultisample::copy_range(const Vector2u& dimensions, const Vector2u& offset, Format dataFormat, std::span<const byte> data, unsigned int mipLevel, bool generateMips)
    {
        if (data.empty()) return;
        if (const auto size = m_dimensions.x * m_dimensions.y * static_cast<unsigned int>(dataFormat); size != data.size()) throw std::invalid_argument{ "Data length does not match texture size!" };
        if (const auto totalSize = Vector2u{ offset.x + dimensions.x, offset.y + dimensions.y }; totalSize.x > m_dimensions.x || totalSize.y > m_dimensions.y) throw std::out_of_range{ "Image dimensions are not within texture bounds!" };

        const auto format = OpenGL::texture_format(dataFormat);
        glTextureSubImage2D(m_id, mipLevel, offset.x, offset.y, dimensions.x, dimensions.y, format, GL_UNSIGNED_BYTE, data.data());
        if (generateMips) glGenerateTextureMipmap(m_id);
    }
}
