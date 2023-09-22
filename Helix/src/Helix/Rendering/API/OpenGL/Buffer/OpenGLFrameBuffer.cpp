#include "stdafx.hpp"

#include "OpenGLFrameBuffer.hpp"

namespace hlx
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(const Vector2u& dimensions, std::span<const TextureManifest> textureManifests, std::span<const RenderBufferManifest> renderBufferManifests)
		: FrameBuffer{ dimensions }
	{
		m_id = OpenGL::create_framebuffer();

		std::vector<GLenum> buffers{};
		unsigned int textureAttachmentIndex{};
		for (const auto& textureManifest : textureManifests)
		{
			const auto& drawBuffer = attach_texture(textureManifest, textureAttachmentIndex);
			buffers.push_back(drawBuffer);
		}
		for (const auto& renderBufferManifest : renderBufferManifests)
		{
			attach_renderbuffer(renderBufferManifest);
		}

		if (buffers.empty()) 
		{
			OpenGL::framebuffer_readbuffer(m_id, GL_NONE);
			OpenGL::framebuffer_drawbuffer(m_id, GL_NONE);
		}
		else
		{
			OpenGL::framebuffer_drawbuffers(m_id, buffers);
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

    GLenum OpenGLFrameBuffer::attach_texture(const TextureManifest& textureManifest, unsigned int& attachmentIndex)
    {
		const auto& [name, attachment, blueprint] = textureManifest;
        const auto& glTexture = std::static_pointer_cast<OpenGLTexture2D>(blueprint.build(m_dimensions));

        auto internalAttachment = OpenGL::framebuffer_attachment(attachment);
        if (attachment == Attachment::Color)
        {
            internalAttachment += attachmentIndex;
            ++attachmentIndex;
        }

        OpenGL::attach_framebuffer_texture(m_id, glTexture->id(), internalAttachment, 0);
        m_textures.emplace(name, glTexture);

		return internalAttachment;
    }
    void   OpenGLFrameBuffer::attach_renderbuffer(const RenderBufferManifest& renderBufferManifest)
    {
		const auto& [name, attachment, blueprint] = renderBufferManifest;
		const auto& glRenderBuffer = std::static_pointer_cast<OpenGLRenderBuffer>(blueprint.build(m_dimensions));

		const auto& internalAttachment = OpenGL::framebuffer_attachment(attachment);

		OpenGL::attach_framebuffer_renderbuffer(m_id, glRenderBuffer->id(), internalAttachment);
		m_renderBuffers.emplace(name, glRenderBuffer);
    }
}
