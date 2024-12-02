#pragma once

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/Texture/Texture.hpp"

namespace fox::gfx::api::gl
{
    template<AntiAliasing AA>
    class RenderBuffer : public api::Texture, public gl::Object
    {
    public:
        RenderBuffer(Format format, const fox::Vector2u& dimensions) requires (AA == AntiAliasing::None)
            : api::Texture{ format, Texture::Filter::None, Texture::Wrapping::Repeat }, m_dimensions{ dimensions }
        {
            m_handle = gl::create_render_buffer();

            const auto& renderBufferFormat = gl::map_render_buffer_format(format);
            gl::render_buffer_storage(m_handle, renderBufferFormat, m_dimensions);
        }
        RenderBuffer(Format format, const fox::Vector2u& dimensions, fox::count_t samples) requires (AA == AntiAliasing::MSAA)
            : Texture{ format, Texture::Filter::None, Texture::Wrapping::Repeat }, m_dimensions{ dimensions }, m_samples{ samples }
        {
            m_handle = gl::create_render_buffer();

            const auto& renderBufferFormat = gl::map_render_buffer_format(format);
            gl::render_buffer_storage_multisample(m_handle, renderBufferFormat, m_dimensions, m_samples);
        }
        RenderBuffer(RenderBuffer&& other) noexcept
        {
            *this = std::move(other);
        }
        ~RenderBuffer()
        {
            gl::delete_render_buffer(m_handle);
        }

        const fox::Vector2u& dimensions() const
        {
            return m_dimensions;
        }
        fox::count_t         samples()    const
        {
            return m_samples;
        }

        RenderBuffer& operator=(RenderBuffer&& other) noexcept
        {
            m_handle     = other.m_handle;
            m_dimensions = other.m_dimensions;
            m_samples    = other.m_samples;

            other.m_handle     = {};
            other.m_dimensions = {};
            other.m_samples    = 0u;

            return *this;
        }

    private:
        fox::Vector2u m_dimensions{};
        fox::count_t  m_samples{};
    };
}
