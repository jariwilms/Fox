#pragma once

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/API/Implementation/GRenderBuffer.hpp"

namespace hlx::gfx::imp::api
{
    template<AntiAliasing AA>
    class GRenderBuffer<gfx::api::GraphicsAPI::OpenGL, AA> : public Texture
    {
    public:
        GRenderBuffer(Format format, const Vector2u& dimensions)             requires (AA == AntiAliasing::None)
            : Texture{ format, Texture::Filter::None, Texture::Wrapping::Repeat }, m_dimensions{ dimensions }
        {
            m_glId = gl::create_render_buffer();

            const auto& glFormat = gl::render_buffer_format(format);
            gl::render_buffer_storage(m_glId, glFormat, this->m_dimensions);
        }
        GRenderBuffer(Format format, const Vector2u& dimensions, u8 samples) requires (AA == AntiAliasing::MSAA)
            : Texture{ format, Texture::Filter::None, Texture::Wrapping::Repeat }, m_dimensions{ dimensions }, m_samples{ samples }
        {
            m_glId = gl::create_render_buffer();

            const auto& glFormat = gl::render_buffer_format(format);
            gl::render_buffer_storage_multisample(m_glId, glFormat, this->m_dimensions, m_samples);
        }
        GRenderBuffer(GRenderBuffer&& other) noexcept
        {
            *this = std::move(other);
        }
        ~GRenderBuffer()
        {
            if (m_glId) gl::delete_render_buffer(m_glId);
        }

        const Vector2u& dimensions() const
        {
            return m_dimensions;
        }
        u8              samples()    const
        {
            return m_samples;
        }

        auto expose_internals() const
        {
            return InternalView<GRenderBuffer<gfx::api::GraphicsAPI::OpenGL, AA>>
            {
                m_glId
            };
        }

        GRenderBuffer& operator=(GRenderBuffer&& other) noexcept
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
        GLuint m_glId{};

        Vector2u m_dimensions{};
        u8       m_samples{};
    };
}
