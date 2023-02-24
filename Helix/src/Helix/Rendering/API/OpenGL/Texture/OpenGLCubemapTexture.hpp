#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/CubemapTexture.hpp"

namespace hlx
{
    class OpenGLCubemapTexture : public CubemapTexture
    {
    public:
        OpenGLCubemapTexture(Format format, Layout layout, const Vector2u& dimensions, unsigned int mipLevels, Wrapping wrappingS, Wrapping wrappingT, Wrapping wrappingR, Filter filter, const std::array<std::span<const byte>, 6>& data = {});
        ~OpenGLCubemapTexture();

        void bind() const override;
        void bind(unsigned int slot) const override;
        void unbind() const override;
        bool bound() const override;

        void copy(const std::array<std::span<const byte>, 6>& data, unsigned int mipLevel = 0, bool generateMips = true) override;
        void copy_range(const Vector2u dimensions, const Vector2u& offset, const std::array<std::span<const byte>, 6>& data, unsigned int mipLevel = 0, bool generateMips = true) override;

    private:
        GLenum m_internalTarget{ GL_TEXTURE_CUBE_MAP };
        GLenum m_internalFormat{};
        GLenum m_internalLayout{};
    };
}
