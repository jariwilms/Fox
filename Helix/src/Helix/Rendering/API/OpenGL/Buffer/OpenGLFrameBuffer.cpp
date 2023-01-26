#include "stdafx.hpp"

#include "OpenGLFrameBuffer.hpp"

namespace hlx
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(const glm::uvec2& dimensions, const std::vector<std::tuple<std::string, Attachment, TextureBlueprint>>& textures, const std::vector<std::tuple<std::string, Attachment, RenderBufferBlueprint>>& renderBuffers)
		: FrameBuffer{ dimensions }
	{
		glCreateFramebuffers(1, &m_id);

		unsigned int colorAttachmentIndex{};
		std::vector<GLenum> drawBuffers{};
		const auto attach_texture = [this, &drawBuffers, &colorAttachmentIndex](const std::tuple<std::string, Attachment, TextureBlueprint>& value)
		{
			const auto& [name, attachment, blueprint] = value;
			const auto texture = blueprint.build(m_dimensions, 1);

			auto internalAttachment = OpenGL::framebuffer_attachment(attachment);
			if (attachment == Attachment::Color)
			{
				internalAttachment += colorAttachmentIndex;
				++colorAttachmentIndex;

				drawBuffers.emplace_back(internalAttachment);
			}

			glNamedFramebufferTexture(m_id, internalAttachment, texture->id(), 0);
			m_attachedTextures.emplace(name, texture);
		};
		const auto attach_renderbuffer = [this](const std::tuple<std::string, Attachment, RenderBufferBlueprint>& attachee)
		{
			const auto& [name, attachment, blueprint] = attachee;
			const auto renderBuffer = blueprint.build(m_dimensions, 0);

			auto internalAttachment = OpenGL::framebuffer_attachment(attachment);

            glNamedFramebufferRenderbuffer(m_id, internalAttachment, GL_RENDERBUFFER, renderBuffer->id());
		};

		std::for_each(textures.begin(), textures.end(), attach_texture);
		std::for_each(renderBuffers.begin(), renderBuffers.end(), attach_renderbuffer);
		glNamedFramebufferDrawBuffers(m_id, static_cast<GLsizei>(drawBuffers.size()), drawBuffers.data());

		const auto status = glCheckNamedFramebufferStatus(m_id, GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE) throw std::runtime_error{ "Failed to create framebuffer!" };
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_id);
	}

	void OpenGLFrameBuffer::bind() const
	{
		throw std::logic_error{ "Method has not been implemented!" };
	}
	void OpenGLFrameBuffer::bind(FrameBuffer::Target target) const
	{
		glBindFramebuffer(OpenGL::framebuffer_target(target), m_id);
	}
	void OpenGLFrameBuffer::unbind() const
	{
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	bool OpenGLFrameBuffer::is_bound() const
	{
		return false;
	}

    void OpenGLFrameBuffer::bind_texture(const std::string identifier, unsigned int slot)
    {
		auto texture = m_attachedTextures.find(identifier);
		if (texture == m_attachedTextures.end()) throw std::runtime_error{ "Given texture identifier does not exist!" };

		texture->second->bind(slot);
    }
}
