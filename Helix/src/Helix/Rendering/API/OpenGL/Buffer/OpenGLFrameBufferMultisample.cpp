#include "stdafx.hpp"

#include "OpenGLFrameBufferMultisample.hpp"

namespace hlx
{
    OpenGLFrameBufferMultisample::OpenGLFrameBufferMultisample(const Vector2u& dimensions, unsigned int samples, const std::vector<std::tuple<std::string, Attachment, TextureBlueprint>>& textures, const std::vector<std::tuple<std::string, Attachment, RenderBufferBlueprint>>& renderBuffers)
        : FrameBufferMultisample{ dimensions, samples }
    {
        if (m_samples == 0) throw std::invalid_argument{ "Samples must be greater than zero!" };

        glCreateFramebuffers(1, &m_id);

        unsigned int colorAttachmentIndex{};
        std::vector<GLenum> drawBuffers{};
        const auto attach_texture = [this, &drawBuffers, &colorAttachmentIndex](const std::tuple<std::string, Attachment, TextureBlueprint>& value)
        {
            const auto& [name, attachment, blueprint] = value;
            const auto texture = blueprint.build_ms(m_dimensions, 1, m_samples);

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
            const auto renderBuffer = blueprint.build_ms(m_dimensions, m_samples);

            auto internalAttachment = OpenGL::framebuffer_attachment(attachment);

            glNamedFramebufferRenderbuffer(m_id, internalAttachment, GL_RENDERBUFFER, renderBuffer->id());
        };

        std::for_each(textures.begin(), textures.end(), attach_texture);
        std::for_each(renderBuffers.begin(), renderBuffers.end(), attach_renderbuffer);
        glNamedFramebufferDrawBuffers(m_id, static_cast<GLsizei>(drawBuffers.size()), drawBuffers.data());

        const auto status = glCheckNamedFramebufferStatus(m_id, GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) throw std::runtime_error{ "Failed to create framebuffer!" };
    }
    OpenGLFrameBufferMultisample::~OpenGLFrameBufferMultisample()
    {
        glDeleteFramebuffers(1, &m_id);
    }

    void OpenGLFrameBufferMultisample::bind(FrameBuffer::Target target)
    {
        m_internalBoundTarget = OpenGL::framebuffer_target(target);
        glBindFramebuffer(m_internalBoundTarget, m_id);
    }
    void OpenGLFrameBufferMultisample::unbind() const
    {
        glBindFramebuffer(m_internalBoundTarget, 0);
    }
    bool OpenGLFrameBufferMultisample::is_bound() const
    {
        return false;
    }

    void OpenGLFrameBufferMultisample::bind_texture(const std::string identifier, unsigned int slot)
    {
        auto texture = m_attachedTextures.find(identifier);
        if (texture == m_attachedTextures.end()) throw std::runtime_error{ "Given texture identifier does not exist!" };

        texture->second->bind(slot);
    }
}
