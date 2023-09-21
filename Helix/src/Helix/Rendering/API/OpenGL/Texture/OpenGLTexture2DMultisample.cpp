#include "stdafx.hpp"

#include "OpenGLTexture2DMultisample.hpp"

namespace hlx
{
    OpenGLTexture2DMultisample::OpenGLTexture2DMultisample(Format format, const Vector2u& dimensions, unsigned int samples)
        : Texture2DMultisample{ format, dimensions, samples }
    {
        m_internalId     = OpenGL::create_texture(GL_TEXTURE_2D_MULTISAMPLE);
        m_internalFormat = OpenGL::texture_format(m_format);

        OpenGL::texture_storage_2d_multisample(m_internalId, m_internalFormat, m_dimensions, m_samples);
    }
    OpenGLTexture2DMultisample::~OpenGLTexture2DMultisample()
    {
        OpenGL::delete_texture(m_internalId);
    }

    void OpenGLTexture2DMultisample::bind(unsigned int slot) const
    {
        OpenGL::bind_texture(m_internalId, slot);
    }
}
