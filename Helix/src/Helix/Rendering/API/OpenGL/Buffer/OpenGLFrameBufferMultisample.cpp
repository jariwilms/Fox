#include "stdafx.hpp"

#include "OpenGLFrameBufferMultisample.hpp"

namespace hlx
{
    OpenGLFrameBufferMultisample::OpenGLFrameBufferMultisample(const Vector2u& dimensions, unsigned int samples, std::span<const FrameBuffer::Texture2DBlueprintSpec> textures, std::span<const FrameBuffer::RenderBufferBlueprintSpec> renderBuffers)
        : FrameBufferMultisample{ dimensions, samples }
    {
        if (m_samples == 0) throw std::invalid_argument{ "Samples must be greater than zero!" };

        glCreateFramebuffers(1, &m_internalId);

        unsigned int colorAttachmentIndex{};
        std::vector<GLenum> drawBuffers{};
        const auto attach_texture = [this, &drawBuffers, &colorAttachmentIndex](const std::tuple<std::string, Attachment, TextureBlueprint>& value)
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
        const auto attach_renderbuffer = [this](const std::tuple<std::string, Attachment, RenderBufferBlueprint>& attachee)
        {
            const auto& [name, attachment, blueprint] = attachee;
            const auto& renderBuffer = blueprint.build_ms(m_dimensions, m_samples);
            const auto& glRenderBuffer = std::static_pointer_cast<OpenGLRenderBufferMultisample>(renderBuffer);

            auto internalAttachment = OpenGL::framebuffer_attachment(attachment);

            glNamedFramebufferRenderbuffer(m_internalId, internalAttachment, GL_RENDERBUFFER, glRenderBuffer->internal_id());
        };

        std::for_each(textures.begin(),      textures.end(),      attach_texture);
        std::for_each(renderBuffers.begin(), renderBuffers.end(), attach_renderbuffer);
        glNamedFramebufferDrawBuffers(m_internalId, static_cast<GLsizei>(drawBuffers.size()), drawBuffers.data());

        const auto& status = glCheckNamedFramebufferStatus(m_internalId, GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) throw std::runtime_error{ "Failed to create framebuffer!" };
    }
    OpenGLFrameBufferMultisample::~OpenGLFrameBufferMultisample()
    {
        glDeleteFramebuffers(1, &m_internalId);
    }

    void OpenGLFrameBufferMultisample::bind(Target target) const
    {
        const auto& internalTarget = OpenGL::framebuffer_target(target);
        const auto& pair = s_targetToIdMap.try_emplace(internalTarget, 0);
        if (pair.first->second == m_internalId) return;

        glBindFramebuffer(internalTarget, m_internalId);
        s_targetToIdMap.at(internalTarget) = m_internalId;
        s_idToTargetMap.insert_or_assign(m_internalId, internalTarget);
    }
    void OpenGLFrameBufferMultisample::unbind() const
    {
        const auto& it = s_idToTargetMap.find(m_internalId);
        if (it == s_idToTargetMap.end()) return;

        const auto& target = it->first;
        glBindFramebuffer(target, 0);
        s_targetToIdMap.at(target) = 0;
        s_idToTargetMap.at(m_internalId) = 0;
    }
    bool OpenGLFrameBufferMultisample::is_bound() const
    {
        const auto& it = s_idToTargetMap.find(m_internalId);
        if (it == s_idToTargetMap.end()) return false;

        return it->first != 0;
    }

    void OpenGLFrameBufferMultisample::bind_texture(const std::string& identifier, unsigned int slot) const
    {
        const auto& it = m_attachedTextures.find(identifier);
        if (it == m_attachedTextures.end()) throw std::runtime_error{ "Given texture identifier does not exist!" };

        it->second->bind(slot);
    }
}
