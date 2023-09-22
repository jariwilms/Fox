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

        GLenum internal_id() const
        {
            return m_id;
        }

    protected:
        void copy(Components components, std::span<std::span<const byte>, 6> data) override;
        void copy_face(Face face, Components components, std::span<const byte> data) override;
        void copy_face_range(Face face, const Vector2u& dimensions, const Vector2u& offset, Components components, std::span<const byte> data) override;

    private:
        GLenum m_id{};
    };
}
