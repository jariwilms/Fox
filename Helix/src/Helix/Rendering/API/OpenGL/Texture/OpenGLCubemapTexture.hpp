#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/CubemapTexture.hpp"

namespace hlx
{
    class OpenGLCubemapTexture : public CubemapTexture
    {
    public:
        OpenGLCubemapTexture(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions);
        OpenGLCubemapTexture(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions, Components components, std::span<std::span<const byte>, 6> data);
        ~OpenGLCubemapTexture();

        void bind(unsigned int slot) const override;

        GLenum internal_id()         const
        {
            return m_internalId;
        }
        GLenum internal_format()     const
        {
            return m_internalFormat;
        }
        GLenum internal_min_filter() const
        {
            return m_internalMinFilter;
        }
        GLenum internal_mag_filter() const
        {
            return m_internalMagFilter;
        }
        GLenum internal_wrapping()   const
        {
            return m_internalWrapping;
        }

    protected:
        void copy(Components components, std::span<std::span<const byte>, 6> data) override;
        void copy_face(Face face, Components components, std::span<const byte> data) override;
        void copy_face_range(Face face, const Vector2u& dimensions, const Vector2u& offset, Components components, std::span<const byte> data) override;

    private:
        GLenum m_internalId{};
        GLenum m_internalFormat{};
        GLenum m_internalMinFilter{};
        GLenum m_internalMagFilter{};
        GLenum m_internalWrapping{};
    };
}
