#include "stdafx.hpp"

#include "OpenGLRenderBuffer.hpp"

namespace hlx
{
	OpenGLRenderBuffer::OpenGLRenderBuffer(RenderBuffer::Type type, RenderBuffer::Layout layout, const Vector2u& dimensions)
		: RenderBuffer{ type, layout, dimensions }
	{
		m_internalTarget = GL_RENDERBUFFER;
		m_internalFormat = OpenGL::renderbuffer_layout(layout);

		glCreateRenderbuffers(1, &m_internalId);
		glNamedRenderbufferStorage(m_internalId, m_internalFormat, m_dimensions.x, m_dimensions.y);
	}
	OpenGLRenderBuffer::~OpenGLRenderBuffer()
	{
		glDeleteRenderbuffers(1, &m_internalId);
	}

	void OpenGLRenderBuffer::bind()     const
	{
		glBindRenderbuffer(m_internalTarget, m_internalId);
	}
    void OpenGLRenderBuffer::unbind()   const
	{
		if (m_internalId != s_boundRenderBufferId) return;

		glBindRenderbuffer(m_internalTarget, 0);
	}
    bool OpenGLRenderBuffer::is_bound() const
	{
		return m_internalId == s_boundRenderBufferId;
	}
}
