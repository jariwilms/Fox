#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Buffer/RenderBufferMultisample.hpp"

namespace hlx
{
    class OpenGLRenderBufferMultisample : public RenderBufferMultisample
    {
    public:
        OpenGLRenderBufferMultisample(Format format, const Vector2u& dimensions, unsigned int samples);
        ~OpenGLRenderBufferMultisample();

        void bind() const override;

        GLuint id() const
        {
            return m_id;
        }

    private:
        GLuint m_id{};
    };
}
