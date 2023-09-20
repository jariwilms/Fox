#include "stdafx.hpp"

#include "OpenGLFrameBufferMultisample.hpp"

namespace hlx
{
    OpenGLFrameBufferMultisample::OpenGLFrameBufferMultisample(const Vector2u& dimensions, unsigned int samples, std::span<const TextureManifest> textureManifest, std::span<const RenderBufferManifest> renderBufferManifest)
        : FrameBufferMultisample{ dimensions, samples }
    {
        if (m_samples == 0) throw std::invalid_argument{ "Samples must be greater than zero!" };

        glCreateFramebuffers(1, &m_internalId);

        unsigned int colorAttachmentIndex{};
        std::vector<GLenum> drawBuffers{};
        const auto attach_texture = [this, &drawBuffers, &colorAttachmentIndex](const TextureManifest& value)
        {
            const auto& [name, attachment, blueprint] = value;
            const auto& texture = blueprint.build_ms(m_dimensions, m_samples);
            const auto& glTexture = std::static_pointer_cast<OpenGLTexture2DMultisample>(texture);

            auto internalAttachment = OpenGL::framebuffer_attachment(attachment);
            if (attachment == Attachment::Color)
            {
                internalAttachment += colorAttachmentIndex;
                ++colorAttachmentIndex;

                drawBuffers.emplace_back(internalAttachment);
            }

            glNamedFramebufferTexture(m_internalId, internalAttachment, glTexture->internal_id(), 0);
            m_attachedTextures.emplace(name, texture);
        };
        const auto attach_renderbuffer = [this](const RenderBufferManifest& attachee)
        {
            const auto& [name, attachment, blueprint] = attachee;
            const auto& renderBuffer = blueprint.build_ms(m_dimensions, m_samples);
            const auto& glRenderBuffer = std::static_pointer_cast<OpenGLRenderBufferMultisample>(renderBuffer);

            auto internalAttachment = OpenGL::framebuffer_attachment(attachment);

            glNamedFramebufferRenderbuffer(m_internalId, internalAttachment, GL_RENDERBUFFER, glRenderBuffer->internal_id());
        };

        std::for_each(textureManifest.begin(),      textureManifest.end(),      attach_texture);
        std::for_each(renderBufferManifest.begin(), renderBufferManifest.end(), attach_renderbuffer);
        glNamedFramebufferDrawBuffers(m_internalId, static_cast<GLsizei>(drawBuffers.size()), drawBuffers.data());

        const auto& status = glCheckNamedFramebufferStatus(m_internalId, GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) throw std::runtime_error{ "Failed to create framebuffer!" };
    }
    OpenGLFrameBufferMultisample::~OpenGLFrameBufferMultisample()
    {
        glDeleteFramebuffers(1, &m_internalId);
    }

    void OpenGLFrameBufferMultisample::bind(FrameBuffer::Target target) const
    {
        const auto& internalTarget = OpenGL::framebuffer_target(target);
        glBindFramebuffer(internalTarget, m_internalId);
    }
    void OpenGLFrameBufferMultisample::unbind() const
    {
        throw std::logic_error{ "Method has not been implemented!" };
    }
    bool OpenGLFrameBufferMultisample::is_bound() const
    {
        throw std::logic_error{ "Method has not been implemented!" };
    }

    void OpenGLFrameBufferMultisample::bind_texture(const std::string& identifier, unsigned int slot) const
    {
        const auto& it = m_attachedTextures.find(identifier);
        if (it == m_attachedTextures.end()) throw std::runtime_error{ "Given texture identifier does not exist!" };

        it->second->bind(slot);
    }
}
