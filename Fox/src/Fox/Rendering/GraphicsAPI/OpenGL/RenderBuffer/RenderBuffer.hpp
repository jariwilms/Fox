#pragma once

#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/API/RenderBuffer/RenderBuffer.hpp"

namespace fox::gfx::api::gl
{
    template<api::AntiAliasing = api::AntiAliasing::None>
    class RenderBuffer;

    template<>
    class RenderBuffer<api::AntiAliasing::None> : public api::RenderBuffer, public gl::Object
    {
    public:
        RenderBuffer(Format format, const fox::Vector2u& dimensions)
            : api::RenderBuffer{ format }, m_dimensions{ dimensions }
        {
            m_handle = gl::create_render_buffer();

            const auto& renderBufferFormat = gl::map_render_buffer_format(format);
            gl::render_buffer_storage(m_handle, renderBufferFormat, m_dimensions);
        }
        RenderBuffer(RenderBuffer&&) noexcept = default;
        ~RenderBuffer()
        {
            gl::delete_render_buffer(m_handle);
        }

        const fox::Vector2u& dimensions() const
        {
            return m_dimensions;
        }

        RenderBuffer& operator=(RenderBuffer&&) noexcept = default;

    private:
        fox::Vector2u m_dimensions{};
    };
    template<>
    class RenderBuffer<api::AntiAliasing::MSAA> : public api::RenderBuffer, public gl::Object
    {
    public:
        RenderBuffer(Format format, const fox::Vector2u& dimensions, fox::uint8_t samples)
            : api::RenderBuffer{ format }, m_dimensions{ dimensions }, m_samples{ samples }
        {
            m_handle = gl::create_render_buffer();

            const auto& renderBufferFormat = gl::map_render_buffer_format(format);
            gl::render_buffer_storage_multisample(m_handle, renderBufferFormat, m_dimensions, m_samples);
        }
        RenderBuffer(RenderBuffer&&) noexcept = default;
        ~RenderBuffer()
        {
            gl::delete_render_buffer(m_handle);
        }

        const fox::Vector2u& dimensions() const
        {
            return m_dimensions;
        }
        fox::uint8_t         samples() const
        {
            return m_samples;
        }

        RenderBuffer& operator=(RenderBuffer&&) noexcept = default;

    private:
        fox::Vector2u m_dimensions{};
        fox::uint8_t  m_samples{};
    };
}
