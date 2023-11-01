#pragma once

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Texture.hpp"

namespace hlx::gfx::api
{
    template<AntiAliasing A>
    class GRenderBuffer : public Texture
    {
    public:
        GRenderBuffer(Format format, const Vector2u& dimensions)             requires (A == AntiAliasing::None)
            : Texture{ format, Texture::Filter::None, Texture::Wrapping::Repeat }, m_dimensions{ dimensions }
        {
            m_glId = gl::create_render_buffer();

            const auto& glFormat = gl::render_buffer_format(format);
            gl::render_buffer_storage(m_glId, glFormat, this->m_dimensions);
        }
        GRenderBuffer(Format format, const Vector2u& dimensions, u8 samples) requires (A == AntiAliasing::MSAA)
            : Texture{ format, Texture::Filter::None, Texture::Wrapping::Repeat }, m_dimensions{ dimensions }, m_samples{ samples }
        {
            m_glId = gl::create_render_buffer();

            const auto& glFormat = gl::render_buffer_format(format);
            gl::render_buffer_storage_multisample(m_glId, glFormat, this->m_dimensions, m_samples);
        }
        ~GRenderBuffer()
        {
            gl::delete_render_buffer(m_glId);
        }

        const Vector2u& dimensions() const
        {
            return m_dimensions;
        }
        u8              samples()    const
        {
            return m_samples;
        }

    private:
        GLuint m_glId{};

        Vector2u m_dimensions{};
        u8       m_samples{};
    };
}
