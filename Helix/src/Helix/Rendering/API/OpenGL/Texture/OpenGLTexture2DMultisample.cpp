#include "stdafx.hpp"

#include "OpenGLTexture2DMultisample.hpp"

namespace hlx
{
    OpenGLTexture2DMultisample::OpenGLTexture2DMultisample(Format format, Layout layout, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, Wrapping wrappingS, Wrapping wrappingT, Filter filter, std::span<const byte> data)
        : Texture2DMultisample{ format, layout, dimensions, mipLevels, samples, wrappingS, wrappingT, filter }
    {
        m_internalFormat = OpenGL::texture_format(m_format);
        m_internalLayout = OpenGL::texture_layout(m_layout);

        glCreateTextures(m_internalTarget, 1, &m_id);
        glTextureStorage2DMultisample(m_id, m_samples, m_internalLayout, m_dimensions.x, m_dimensions.y, GL_TRUE);

        copy(data);
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

    void OpenGLTexture2DMultisample::copy(std::span<const byte> data, unsigned int mipLevel, bool generateMips)
    {
        if (data.empty()) return;
        if (const auto size = m_dimensions.x * m_dimensions.y * 4; size != data.size()) throw std::invalid_argument{ "Data length does not match texture size!" };

        glTextureSubImage2D(m_id, mipLevel, 0, 0, m_dimensions.x, m_dimensions.y, m_internalFormat, GL_UNSIGNED_BYTE, data.data());
    }
    void OpenGLTexture2DMultisample::copy_range(const Vector2u& dimensions, const Vector2u& offset, std::span<const byte> data, unsigned int mipLevel, bool generateMips)
    {
        if (data.empty()) return;
        if (offset.x + dimensions.x > m_dimensions.x || offset.y + dimensions.y > m_dimensions.y) throw std::out_of_range{ "Data dimensions are not within texture bounds!" };

        glTextureSubImage2D(m_id, mipLevel, offset.x, offset.y, dimensions.x, dimensions.y, m_internalFormat, GL_UNSIGNED_BYTE, data.data());

    }
}
