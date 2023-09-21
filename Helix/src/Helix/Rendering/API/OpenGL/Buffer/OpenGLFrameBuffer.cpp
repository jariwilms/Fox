#include "stdafx.hpp"

#include "OpenGLFrameBuffer.hpp"

namespace hlx
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(const Vector2u& dimensions, std::span<const TextureManifest> textureManifest, std::span<const RenderBufferManifest> renderBufferManifest)
		: FrameBuffer{ dimensions }
	{
		m_id = OpenGL::create_framebuffer();

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

			OpenGL::attach_framebuffer_texture(m_id, glTexture->internal_id(), internalAttachment, 0);
			m_textures.emplace(name, texture);
		};
		const auto attach_renderbuffer = [this](const RenderBufferManifest& attachee)
		{
			const auto& [name, attachment, blueprint] = attachee;
			const auto& renderBuffer = blueprint.build(m_dimensions);
			const auto& glRenderBuffer = std::static_pointer_cast<OpenGLRenderBuffer>(renderBuffer);

			auto internalAttachment = OpenGL::framebuffer_attachment(attachment);
			OpenGL::attach_framebuffer_renderbuffer(m_id, glRenderBuffer->id(), internalAttachment);
		};

		std::for_each(textureManifest.begin(),      textureManifest.end(),      attach_texture);
		std::for_each(renderBufferManifest.begin(), renderBufferManifest.end(), attach_renderbuffer);

		if (drawBuffers.empty()) 
		{
			glNamedFramebufferDrawBuffer(m_id, GL_NONE);
			glNamedFramebufferReadBuffer(m_id, GL_NONE);
		}
		else
		{
			glNamedFramebufferDrawBuffers(m_id, static_cast<GLsizei>(drawBuffers.size()), drawBuffers.data());
		}

		OpenGL::check_framebuffer_status(m_id);
	}
    OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		OpenGL::delete_framebuffer(m_id);
	}

	void OpenGLFrameBuffer::bind(Target target) const
	{
		OpenGL::bind_framebuffer(m_id, target);
	}
    void OpenGLFrameBuffer::bind_texture(const std::string& identifier, unsigned int slot) const
    {
		m_textures.at(identifier)->bind(slot);
    }
}
