#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Buffer/RenderBufferMultisample.hpp"

namespace hlx
{
    class OpenGLRenderBufferMultisample : public RenderBufferMultisample
    {
    public:
        OpenGLRenderBufferMultisample(RenderBuffer::Type type, RenderBuffer::Layout layout, const Vector2u& dimensions, unsigned int samples);
        ~OpenGLRenderBufferMultisample();

        void bind() const override;
        void unbind() const override;
        bool bound() const override;

    private:
        GLenum m_internalTarget{ GL_RENDERBUFFER };
        GLenum m_internalFormat{};
    };
}
