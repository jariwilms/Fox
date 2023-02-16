#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/CubemapTexture.hpp"

namespace hlx
{
    class OpenGLCubemapTexture : public CubemapTexture
    {
    public:
        OpenGLCubemapTexture(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels);
        OpenGLCubemapTexture(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, std::array<std::span<byte>, 6>& data);
        ~OpenGLCubemapTexture();

        void bind() const override;
        void bind(unsigned int slot) const override;
        void unbind() const override;
        bool bound() const override;

        void copy(const Vector2u dimensions, const Vector2u& offset, std::array<std::span<byte>, 6>& data) const override;

    private:
        GLenum m_internalTarget{ GL_TEXTURE_CUBE_MAP };
        GLenum m_internalFormat{};
        GLenum m_internalLayout{};
    };
}
