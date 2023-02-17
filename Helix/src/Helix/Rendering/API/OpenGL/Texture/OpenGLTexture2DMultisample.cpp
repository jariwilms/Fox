#include "stdafx.hpp"

#include "OpenGLTexture2DMultisample.hpp"

namespace hlx
{
    OpenGLTexture2DMultisample::OpenGLTexture2DMultisample(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples)
        : Texture2DMultisample{ format, layout, dimensions, mipLevels, samples }
    {
        m_internalFormat = OpenGL::texture_format(m_format);
        m_internalLayout = OpenGL::texture_layout(m_layout);

        glCreateTextures(m_internalTarget, 1, &m_id);
        glTextureStorage2DMultisample(m_id, m_samples, m_internalLayout, m_dimensions.x, m_dimensions.y, GL_TRUE);
    }
    OpenGLTexture2DMultisample::OpenGLTexture2DMultisample(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, std::span<const byte> data)
        : OpenGLTexture2DMultisample{ format, layout, dimensions, mipLevels, samples }
    {
        copy(dimensions, {}, data);
    }
    OpenGLTexture2DMultisample::OpenGLTexture2DMultisample(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter)
        : Texture2DMultisample{ format, layout, dimensions, mipLevels, samples, wrappingS, wrappingT, minFilter, magFilter }
    {
        m_internalFormat = OpenGL::texture_format(m_format);
        m_internalLayout = OpenGL::texture_layout(m_layout);

        glCreateTextures(m_internalTarget, 1, &m_id);
        glTextureStorage2DMultisample(m_id, m_samples, m_internalLayout, m_dimensions.x, m_dimensions.y, GL_TRUE);
    }
    OpenGLTexture2DMultisample::OpenGLTexture2DMultisample(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter, std::span<const byte> data)
        : OpenGLTexture2DMultisample{ format, layout, dimensions, mipLevels, samples, wrappingS, wrappingT, minFilter, magFilter }
    {
        copy(dimensions, {}, data);
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

    void OpenGLTexture2DMultisample::copy(const Vector2u& dimensions, const Vector2u& offset, std::span<const byte> data) const
    {
        glTextureSubImage2D(m_id, 0, offset.x, offset.y, dimensions.x, dimensions.y, m_internalFormat, GL_UNSIGNED_BYTE, data.data());
        if (m_mipLevels > 1) glGenerateTextureMipmap(m_id);
    }
}
