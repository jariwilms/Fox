#include "stdafx.hpp"

#include "OpenGLFrameBufferMultisample.hpp"

namespace hlx
{
    OpenGLFrameBufferMultisample::OpenGLFrameBufferMultisample(const Vector2u& dimensions, unsigned int samples, std::span<const TextureManifest> textureManifest, std::span<const RenderBufferManifest> renderBufferManifest)
        : FrameBufferMultisample{ dimensions, samples }
    {
        if (m_samples == 0) throw std::invalid_argument{ "Samples must be greater than zero!" };

        glCreateFramebuffers(1, &m_id);

        unsigned int colorAttachmentIndex{};
        std::vector<GLenum> drawBuffers{};
        const auto attach_texture = [this, &drawBuffers, &colorAttachmentIndex](const TextureManifest& value)
        {
            const auto& [name, attachment, blueprint] = value;
            const auto& texture = blueprint.build_multisample(m_dimensions, m_samples);
            const auto& glTexture = std::static_pointer_cast<OpenGLTexture2DMultisample>(texture);

            auto internalAttachment = OpenGL::framebuffer_attachment(attachment);
            if (attachment == Attachment::Color)
            {
                internalAttachment += colorAttachmentIndex;
                ++colorAttachmentIndex;

                drawBuffers.emplace_back(internalAttachment);
            }

            glNamedFramebufferTexture(m_id, internalAttachment, glTexture->internal_id(), 0);
            m_textures.emplace(name, glTexture);
        };
        const auto attach_renderbuffer = [this](const RenderBufferManifest& attachee)
        {
            const auto& [name, attachment, blueprint] = attachee;
            const auto& renderBuffer = blueprint.build_multisample(m_dimensions, m_samples);
            const auto& glRenderBuffer = std::static_pointer_cast<OpenGLRenderBufferMultisample>(renderBuffer);

            auto internalAttachment = OpenGL::framebuffer_attachment(attachment);

            glNamedFramebufferRenderbuffer(m_id, internalAttachment, GL_RENDERBUFFER, glRenderBuffer->id());
            m_renderBuffers.emplace(name, glRenderBuffer);
        };

        std::for_each(textureManifest.begin(),      textureManifest.end(),      attach_texture);
        std::for_each(renderBufferManifest.begin(), renderBufferManifest.end(), attach_renderbuffer);
        glNamedFramebufferDrawBuffers(m_id, static_cast<GLsizei>(drawBuffers.size()), drawBuffers.data());

        const auto& status = glCheckNamedFramebufferStatus(m_id, GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) throw std::runtime_error{ "Failed to create framebuffer!" };
    }
    OpenGLFrameBufferMultisample::~OpenGLFrameBufferMultisample()
    {
        glDeleteFramebuffers(1, &m_id);
    }

    void OpenGLFrameBufferMultisample::bind(FrameBuffer::Target target) const
    {
        OpenGL::bind_framebuffer(m_id, target);
    }
    void OpenGLFrameBufferMultisample::bind_texture(const std::string& identifier, unsigned int slot) const
    {
        m_textures.at(identifier)->bind(slot);
    }
}
