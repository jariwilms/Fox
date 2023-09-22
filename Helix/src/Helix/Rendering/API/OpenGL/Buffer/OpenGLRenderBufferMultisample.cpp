#include "stdafx.hpp"

#include "OpenGLRenderBufferMultisample.hpp"

namespace hlx
{
    OpenGLRenderBufferMultisample::OpenGLRenderBufferMultisample(Format format, const Vector2u& dimensions, unsigned int samples)
        : RenderBufferMultisample{ format, dimensions, samples }
    {
        m_id = OpenGL::create_renderbuffer();

        const auto& internalFormat = OpenGL::renderbuffer_format(format);
        OpenGL::renderbuffer_storage_multisample(m_id, internalFormat, dimensions, m_samples);
    }
    OpenGLRenderBufferMultisample::~OpenGLRenderBufferMultisample()
    {
        OpenGL::delete_renderbuffer(m_id);
    }

    void OpenGLRenderBufferMultisample::bind() const
    {
        OpenGL::bind_renderbuffer(m_id);
    }
}
