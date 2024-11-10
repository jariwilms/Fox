#pragma once

#include "Fox/Rendering/API/OpenGL/GL.hpp"
#include "Fox/Rendering/Texture/Texture.hpp"

namespace fox::gfx::api::gl
{
    template<AntiAliasing AA>
    class OpenGLRenderBuffer : public Texture
    {
    public:
        OpenGLRenderBuffer(Format format, const Vector2u& dimensions)                       requires (AA == AntiAliasing::None)
            : Texture{ format, Texture::Filter::None, Texture::Wrapping::Repeat }, m_dimensions{ dimensions }
        {
            m_glId = gl::create_render_buffer();

            const auto& glFormat = gl::map_render_buffer_format(format);
            gl::render_buffer_storage(m_glId, glFormat, this->m_dimensions);
        }
        OpenGLRenderBuffer(Format format, const Vector2u& dimensions, std::uint8_t samples) requires (AA == AntiAliasing::MSAA)
            : Texture{ format, Texture::Filter::None, Texture::Wrapping::Repeat }, m_dimensions{ dimensions }, m_samples{ samples }
        {
            m_glId = gl::create_render_buffer();

            const auto& glFormat = gl::map_render_buffer_format(format);
            gl::render_buffer_storage_multisample(m_glId, glFormat, this->m_dimensions, m_samples);
        }
        OpenGLRenderBuffer(OpenGLRenderBuffer&& other) noexcept
        {
            *this = std::move(other);
        }
        ~OpenGLRenderBuffer()
        {
            if (m_glId) gl::delete_render_buffer(m_glId);
        }

        const Vector2u& dimensions() const
        {
            return m_dimensions;
        }
        std::uint8_t    samples()    const
        {
            return m_samples;
        }

        OpenGLRenderBuffer& operator=(OpenGLRenderBuffer&& other) noexcept
        {
            m_glId       = other.m_glId;
            m_dimensions = other.m_dimensions;
            m_samples    = other.m_samples;

            other.m_glId       = 0u;
            other.m_dimensions = {};
            other.m_samples    = 0u;

            return *this;
        }

    private:
        gl::uint32_t m_glId{};

        Vector2u     m_dimensions{};
        std::uint8_t m_samples{};
    };
}
