#include "stdafx.hpp"

#include "OpenGLTexture2DMultisample.hpp"

namespace hlx
{
    OpenGLTexture2DMultisample::OpenGLTexture2DMultisample(Format format, const Vector2u& dimensions, unsigned int samples)
        : Texture2DMultisample{ format, dimensions, samples }
    {
        m_internalTarget   = GL_TEXTURE_2D_MULTISAMPLE;
        m_internalFormat   = OpenGL::texture_format(m_format);
        m_internalWrapping = OpenGL::texture_wrapping(m_wrapping);
        m_samples          = std::min<unsigned int>(m_samples, OpenGL::max_samples());

        glCreateTextures(m_internalTarget, 1, &m_internalId);
        glTextureParameteri(m_internalId, GL_TEXTURE_WRAP_S, m_internalWrapping);
        glTextureParameteri(m_internalId, GL_TEXTURE_WRAP_T, m_internalWrapping);
        glTextureStorage2DMultisample(m_internalId, m_samples, m_internalFormat, m_dimensions.x, m_dimensions.y, GL_TRUE);
    }
    OpenGLTexture2DMultisample::~OpenGLTexture2DMultisample()
    {
        glDeleteTextures(1, &m_internalId);
    }

    void OpenGLTexture2DMultisample::bind(unsigned int slot) const
    {
        const auto& pair = s_slotToIdMap.try_emplace(slot, 0);
        if (pair.first->second == m_internalId) return;

        glBindTextureUnit(slot, m_internalId);
        s_slotToIdMap.at(slot) = m_internalId;
        s_idToSlotMap.insert_or_assign(m_internalId, slot);
    }
    void OpenGLTexture2DMultisample::unbind() const
    {
        const auto& it = s_idToSlotMap.find(m_internalId);
        if (it == s_idToSlotMap.end()) return;

        const auto& slot = it->first;
        glBindTextureUnit(slot, 0);
        s_slotToIdMap.at(slot) = 0;
        s_idToSlotMap.at(m_internalId) = 0;
    }
    bool OpenGLTexture2DMultisample::is_bound() const
    {
        const auto& it = s_idToSlotMap.find(m_internalId);
        if (it == s_idToSlotMap.end()) return false;

        return it->first != 0;
    }
}
