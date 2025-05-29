#pragma once

#include "Fox/Rendering/API/RenderBuffer/RenderBuffer.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"

namespace fox::gfx::api::gl
{
    class RenderBuffer : public gl::Object
    {
    public:
        using Format = api::RenderBuffer::Format;

         RenderBuffer(Format format, const gl::Vector2u& dimensions)
            : m_format{ format }, m_dimensions{ dimensions }
        {
            m_handle = gl::create_render_buffer();

            gl::render_buffer_storage(m_handle, gl::map_render_buffer_format(format), m_dimensions);
        }
        ~RenderBuffer()
        {
            gl::delete_render_buffer(m_handle);
        }

        void resize(const gl::Vector2u& dimensions)
        {
            auto handle = gl::create_render_buffer();

            gl::render_buffer_storage(handle, gl::map_render_buffer_format(m_format), m_dimensions);
            gl::delete_texture       (m_handle);

            m_handle     = handle;
            m_dimensions = dimensions;
        }

        auto format    () const
        {
            return m_format;
        }
        auto dimensions() const
        {
            return m_dimensions;
        }

    private:
        Format       m_format{};
        gl::Vector2u m_dimensions{};
    };
    class RenderBufferMultisample : public gl::Object
    {
    public:
        using Format = api::RenderBuffer::Format;

         RenderBufferMultisample(Format format, const gl::Vector2u& dimensions, gl::uint32_t samples)
            : m_format{ format }, m_dimensions{ dimensions }, m_samples{ samples }
        {
            m_handle = gl::create_render_buffer();

            gl::render_buffer_storage_multisample(m_handle, gl::map_render_buffer_format(format), m_dimensions, m_samples);
        }
        ~RenderBufferMultisample()
        {
            gl::delete_render_buffer(m_handle);
        }

        void resize(const gl::Vector2u& dimensions)
        {
            auto handle = gl::create_render_buffer();

            gl::render_buffer_storage_multisample(handle, gl::map_render_buffer_format(m_format), m_dimensions, m_samples);
            gl::delete_texture                   (m_handle);

            m_handle     = handle;
            m_dimensions = dimensions;
        }

        auto format    () const
        {
            return m_format;
        }
        auto dimensions() const
        {
            return m_dimensions;
        }
        auto samples   () const
        {
            return m_samples;
        }

    private:
        Format       m_format{};
        gl::Vector2u m_dimensions{};
        gl::uint32_t m_samples{};
    };
}
