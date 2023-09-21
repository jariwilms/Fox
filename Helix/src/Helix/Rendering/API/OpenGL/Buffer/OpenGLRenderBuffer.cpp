#include "stdafx.hpp"

#include "OpenGLRenderBuffer.hpp"

namespace hlx
{
	OpenGLRenderBuffer::OpenGLRenderBuffer(RenderBuffer::Format format, const Vector2u& dimensions)
		: RenderBuffer{ format, dimensions }
	{
		m_id = OpenGL::create_renderbuffer();

		const auto& internalFormat = OpenGL::renderbuffer_format(format);
		OpenGL::renderbuffer_storage(m_id, internalFormat, dimensions);
	}
	OpenGLRenderBuffer::~OpenGLRenderBuffer()
	{
		OpenGL::delete_renderbuffer(m_id);
	}

	void OpenGLRenderBuffer::bind()     const
	{
		OpenGL::bind_renderbuffer(m_id);
	}
}
