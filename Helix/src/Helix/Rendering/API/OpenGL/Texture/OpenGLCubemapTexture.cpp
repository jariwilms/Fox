#include "stdafx.hpp"

#include "OpenGLCubemapTexture.hpp"

namespace hlx
{
    OpenGLCubemapTexture::OpenGLCubemapTexture(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels)
        : CubemapTexture{ format, layout, dimensions, mipLevels }
    {
        m_internalFormat = OpenGL::texture_format(m_format);
        m_internalLayout = OpenGL::texture_layout(m_layout);

        glCreateTextures(m_internalTarget, 1, &m_id);
        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, OpenGL::texture_min_filter(m_minFilter));
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, OpenGL::texture_mag_filter(m_magFilter));
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, OpenGL::texture_wrapping(m_wrappingS));
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, OpenGL::texture_wrapping(m_wrappingT));
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_R, OpenGL::texture_wrapping(m_wrappingR));
        glTextureStorage2D(m_id, m_mipLevels, m_internalLayout, m_dimensions.x, m_dimensions.y);
    }
    OpenGLCubemapTexture::OpenGLCubemapTexture(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, std::array<std::span<byte>, 6>& data)
        : OpenGLCubemapTexture{ format, layout, dimensions, mipLevels }
    {
        copy(dimensions, Vector2u{}, data);
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

    void OpenGLCubemapTexture::copy(const Vector2u dimensions, const Vector2u& offset, std::array<std::span<byte>, 6>& data) const
    {
        unsigned int index{};
        for (const auto& image : data)
        {
            glTextureSubImage3D(m_id, 0, 0, 0, index, dimensions.x, dimensions.y, 1, m_internalFormat, GL_UNSIGNED_BYTE, image.data());
            ++index;
        }

        glGenerateTextureMipmap(m_id);
    }
}
