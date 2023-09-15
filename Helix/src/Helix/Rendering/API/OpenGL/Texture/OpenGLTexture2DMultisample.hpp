#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Texture2DMultisample.hpp"

namespace hlx
{
    class OpenGLTexture2DMultisample : public Texture2DMultisample
    {
    public:
        OpenGLTexture2DMultisample(Format format, const Vector2u& dimensions, unsigned int samples);
        ~OpenGLTexture2DMultisample() override;

        void bind(unsigned int slot) const override;
        void unbind() const override;
        bool is_bound() const override;

        GLenum internal_id()       const
        {
            return m_internalId;
        }
        GLenum internal_target()   const
        {
            return m_internalTarget;
        }
        GLenum internal_format()   const
        {
            return m_internalFormat;
        }
        GLenum internal_wrapping() const
        {
            return m_internalWrapping;
        }

    private:
        GLenum m_internalId{};
        GLenum m_internalTarget{};
        GLenum m_internalFormat{};
        GLenum m_internalWrapping{};

        static inline std::unordered_map<unsigned int, GLenum> s_slotToIdMap{};
        static inline std::unordered_map<GLenum, unsigned int> s_idToSlotMap{};
    };
}
