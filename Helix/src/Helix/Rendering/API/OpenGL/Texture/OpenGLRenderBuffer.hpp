#pragma once

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Texture.hpp"

namespace hlx::gfx::api
{
    template<AntiAliasing A>
    class GRenderBuffer : public DTexture<Dimensions::_2D>
    {
    public:
        GRenderBuffer(Format format, const Vector2u& dimensions)             requires (A == AntiAliasing::None)
            : DTexture<Dimensions::_2D>{ format, Texture::Filter::None, Texture::Wrapping::Repeat, dimensions }
        {
            m_glId = gl::create_render_buffer();

            const auto& glFormat = gl::render_buffer_format(format);
            gl::render_buffer_storage(m_glId, glFormat, this->m_dimensions);
        }
        GRenderBuffer(Format format, const Vector2u& dimensions, u8 samples) requires (A == AntiAliasing::MSAA)
            : DTexture<Dimensions::_2D>{ format, Texture::Filter::None, Texture::Wrapping::Repeat, dimensions }, m_samples{ samples }
        {
            m_glId = gl::create_render_buffer();

            const auto& glFormat = gl::render_buffer_format(format);
            gl::render_buffer_storage_multisample(m_glId, glFormat, this->m_dimensions, m_samples);
        }
        ~GRenderBuffer()
        {
            gl::delete_render_buffer(m_glId);
        }

        GLuint id()      const
        {
            return m_glId;
        }
        u8     samples() const
        {
            return m_samples;
        }

    private:
        GLuint m_glId{};
        u8     m_samples{};
    };
}
