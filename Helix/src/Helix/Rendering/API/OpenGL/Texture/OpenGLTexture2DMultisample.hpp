#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Texture2DMultisample.hpp"

namespace hlx
{
    class OpenGLTexture2DMultisample : public Texture2DMultisample
    {
    public:
        OpenGLTexture2DMultisample(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples);
        OpenGLTexture2DMultisample(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, std::span<const byte> data);
        OpenGLTexture2DMultisample(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter);
        OpenGLTexture2DMultisample(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter, std::span<const byte> data);
        ~OpenGLTexture2DMultisample() override;

        void bind() const override;
        void bind(unsigned int slot) const override;
        void unbind() const override;
        bool bound() const override;

        void copy(const Vector2u& dimensions, const Vector2u& offset, std::span<const byte> data) const override;

    private:
        GLenum m_internalTarget{ GL_TEXTURE_2D_MULTISAMPLE };
        GLenum m_internalFormat{};
        GLenum m_internalLayout{};
    };
}
