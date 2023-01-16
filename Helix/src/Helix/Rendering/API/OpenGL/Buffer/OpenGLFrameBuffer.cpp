#include "stdafx.hpp"

#include "OpenGLFrameBuffer.hpp"

namespace hlx
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(const glm::uvec2& dimensions)
		: FrameBuffer{ dimensions }
	{
		static auto colorAttachment = std::make_shared<OpenGLTexture2D>(Texture::Format::RGB, Texture::Layout::RGB8, dimensions);
		static auto depthAttachment = std::make_shared<OpenGLRenderBuffer>(RenderBuffer::Type::DepthStencil, RenderBuffer::Layout::Depth24Stencil8, 0, dimensions);

		glCreateFramebuffers(1, &m_id);
		glNamedFramebufferTexture(m_id, GL_COLOR_ATTACHMENT0, colorAttachment->id(), 0);
		glNamedFramebufferRenderbuffer(m_id, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthAttachment->id());

		const auto status = glCheckNamedFramebufferStatus(m_id, GL_FRAMEBUFFER);
		if (!status) throw std::runtime_error{ "Failed to create framebuffer!" };

		m_attachedTextures.emplace(std::make_pair("Color", std::move(colorAttachment)));
		m_attachedRenderBuffers.emplace(std::make_pair("Depth", std::move(depthAttachment)));
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_id);
	}

	void OpenGLFrameBuffer::bind() const
	{

	}
	void OpenGLFrameBuffer::bind(FrameBuffer::Target target) const
	{
		glBindFramebuffer(OpenGL::framebuffer_target(target), m_id);
	}
	void OpenGLFrameBuffer::unbind() const
	{

	}
	bool OpenGLFrameBuffer::is_bound() const
	{
		return false;
	}
}
