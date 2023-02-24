#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Texture2DMultisample.hpp"

namespace hlx
{
    class OpenGLTexture2DMultisample : public Texture2DMultisample
    {
    public:
        OpenGLTexture2DMultisample(Format format, Layout layout, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, Wrapping wrappingS, Wrapping wrappingT, Filter filter, std::span<const byte> data = {});
        ~OpenGLTexture2DMultisample() override;

        void bind() const override;
        void bind(unsigned int slot) const override;
        void unbind() const override;
        bool bound() const override;

        void copy(std::span<const byte> data, unsigned int mipLevel = 0, bool generateMips = true) override;
        void copy_range(const Vector2u& dimensions, const Vector2u& offset, std::span<const byte> data, unsigned int mipLevel = 0, bool generateMips = true) override;

    private:
        GLenum m_internalTarget{ GL_TEXTURE_2D_MULTISAMPLE };
        GLenum m_internalFormat{};
        GLenum m_internalLayout{};
    };
}
