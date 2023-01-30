#include "stdafx.hpp"

#include "OpenGLRenderBuffer.hpp"

namespace hlx
{
	OpenGLRenderBuffer::OpenGLRenderBuffer(RenderBuffer::Type type, RenderBuffer::Layout layout, const Vector2u& dimensions, unsigned int samples)
		: RenderBuffer{ type, layout, dimensions, samples }
	{
		m_internalFormat = OpenGL::renderbuffer_layout(layout);

		glCreateRenderbuffers(1, &m_id);
		glNamedRenderbufferStorageMultisample(m_id, m_multiSamples, m_internalFormat, dimensions.x, dimensions.y);
	}
	OpenGLRenderBuffer::~OpenGLRenderBuffer()
	{
		glDeleteRenderbuffers(1, &m_id);
	}

	void OpenGLRenderBuffer::bind() const
	{
		glBindRenderbuffer(m_internalTarget, m_id);
	}
    void OpenGLRenderBuffer::unbind() const
	{
		glBindRenderbuffer(m_internalTarget, 0);
	}
    bool OpenGLRenderBuffer::bound() const
	{
		return false;
	}
}
