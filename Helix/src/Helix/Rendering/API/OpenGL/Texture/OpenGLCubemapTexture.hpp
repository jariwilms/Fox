#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/CubemapTexture.hpp"

namespace hlx
{
    class OpenGLCubemapTexture : public CubemapTexture
    {
    public:
        OpenGLCubemapTexture(Format format, ColorDepth colorDepth, const Vector2u& dimensions, Filter filter, Wrapping wrappingR, Wrapping wrappingS, Wrapping wrappingT, unsigned int mipLevels, bool sRGB);
        OpenGLCubemapTexture(Format format, ColorDepth colorDepth, const Vector2u& dimensions, Filter filter, Wrapping wrappingR, Wrapping wrappingS, Wrapping wrappingT, unsigned int mipLevels, bool sRGB, Format dataFormat, std::span<std::span<const byte>, 6> data);
        ~OpenGLCubemapTexture();

        void bind() const override;
        void bind(unsigned int slot) const override;
        void unbind() const override;
        bool is_bound() const override;

        void copy(Format dataFormat, std::span<std::span<const byte>, 6> data, unsigned int mipLevel = 0, bool generateMips = true) override;
        void copy_range(const Vector2u& dimensions, const Vector2u& offset, Format DataFormat, std::span<std::span<const byte>, 6> data, unsigned int mipLevel = 0, bool generateMips = true) override;

    private:
        GLenum m_internalTarget{ GL_TEXTURE_CUBE_MAP };
        GLenum m_internalFormat{};
        GLenum m_internalLayout{};
    };
}
