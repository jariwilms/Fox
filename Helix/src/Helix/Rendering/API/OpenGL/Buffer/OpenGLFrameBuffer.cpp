#include "stdafx.hpp"

#include "OpenGLFrameBuffer.hpp"

namespace hlx
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(const Vector2u& dimensions, std::span<const TextureManifest> textureManifest, std::span<const RenderBufferManifest> renderBufferManifest)
		: FrameBuffer{ dimensions }
	{
		m_internalId = OpenGL::create_framebuffer();

		std::vector<GLenum> drawBuffers{};
		unsigned int textureAttachmentIndex{};
		const auto attach_texture = [this, &drawBuffers, &textureAttachmentIndex](const TextureManifest& value)
		{
			const auto& [name, attachment, blueprint] = value;
			const auto& texture = blueprint.build(m_dimensions);
			const auto& glTexture = std::static_pointer_cast<OpenGLTexture2D>(texture);

			auto internalAttachment = OpenGL::framebuffer_attachment(attachment);
			if (attachment == Attachment::Color)
			{
				internalAttachment += textureAttachmentIndex;
				++textureAttachmentIndex;

				drawBuffers.emplace_back(internalAttachment);
			}

			glNamedFramebufferTexture(m_internalId, internalAttachment, glTexture->internal_id(), 0);
			m_attachedTextures.emplace(name, texture);
		};
		const auto attach_renderbuffer = [this](const RenderBufferManifest& attachee)
		{
			const auto& [name, attachment, blueprint] = attachee;
			const auto& renderBuffer = blueprint.build(m_dimensions);
			const auto& glRenderBuffer = std::static_pointer_cast<OpenGLRenderBuffer>(renderBuffer);

			auto internalAttachment = OpenGL::framebuffer_attachment(attachment);

            glNamedFramebufferRenderbuffer(m_internalId, internalAttachment, GL_RENDERBUFFER, glRenderBuffer->internal_id());
		};

		std::for_each(textureManifest.begin(),      textureManifest.end(),      attach_texture);
		std::for_each(renderBufferManifest.begin(), renderBufferManifest.end(), attach_renderbuffer);

		if (drawBuffers.empty()) 
		{
			glNamedFramebufferDrawBuffer(m_internalId, GL_NONE);
			glNamedFramebufferReadBuffer(m_internalId, GL_NONE);
		}
		else
		{
			glNamedFramebufferDrawBuffers(m_internalId, static_cast<GLsizei>(drawBuffers.size()), drawBuffers.data());
		}

		const auto& status = glCheckNamedFramebufferStatus(m_internalId, GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE) throw std::runtime_error{ "Failed to create framebuffer!" };
	}
    OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_internalId);
	}

	void OpenGLFrameBuffer::bind(Target target) const
	{
		const auto& internalTarget = OpenGL::framebuffer_target(target);
		glBindFramebuffer(internalTarget, m_internalId);
	}
    void OpenGLFrameBuffer::unbind() const
	{
		throw std::logic_error{ "Method has not been implemented!" };
	}
	bool OpenGLFrameBuffer::is_bound() const
	{
        throw std::logic_error{ "Method has not been implemented!" };
	}

    void OpenGLFrameBuffer::bind_texture(const std::string& identifier, unsigned int slot) const
    {
		auto texture = m_attachedTextures.find(identifier);
		if (texture == m_attachedTextures.end()) throw std::runtime_error{ "Texture identifier does not exist!" };

		texture->second->bind(slot);
    }
}
