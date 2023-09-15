#include "stdafx.hpp"

#include "OpenGLRenderBufferMultisample.hpp"

namespace hlx
{
    OpenGLRenderBufferMultisample::OpenGLRenderBufferMultisample(Type type, Layout layout, const Vector2u& dimensions, unsigned int samples)
        : RenderBufferMultisample{ type, layout, dimensions, samples }
    {
        m_internalTarget = GL_RENDERBUFFER;
        m_internalFormat = OpenGL::renderbuffer_layout(layout);

        glCreateRenderbuffers(1, &m_internalId);
        glNamedRenderbufferStorageMultisample(m_internalId, m_samples, m_internalFormat, m_dimensions.x, m_dimensions.y);
    }
    OpenGLRenderBufferMultisample::~OpenGLRenderBufferMultisample()
    {
        glDeleteRenderbuffers(1, &m_internalId);
    }

    void OpenGLRenderBufferMultisample::bind()     const
    {
        glBindRenderbuffer(m_internalTarget, m_internalId);
    }
    void OpenGLRenderBufferMultisample::unbind()   const
    {
        if (m_internalId != s_boundRenderBufferId) return;

        glBindRenderbuffer(m_internalTarget, 0);
    }
    bool OpenGLRenderBufferMultisample::is_bound() const
    {
        return m_internalId == s_boundRenderBufferId;
    }
}
