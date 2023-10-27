#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Experimental/Rendering/Buffer/Buffer.hpp"
#include "Helix/Experimental/Rendering/Buffer/VertexArray.hpp"

namespace hlx::gfx::api
{
    template<Buffer::Type S, typename T>
    class GBuffer<GraphicsAPI::OpenGL, S, T> final : public Buffer
    {
    public:
        GBuffer(std::span<const T> data)
            : Buffer{ data.size_bytes() }
        {
            m_glId = gl::create_buffer();

            const auto& flags = gl::buffer_usage(Buffer::Usage::Dynamic);
            gl::buffer_storage(m_glId, flags, data);
        }
        GBuffer(u32 count)
            : Buffer{ count * sizeof(T) }
        {
            m_glId = gl::create_buffer();

            const auto& flags = gl::buffer_usage(Buffer::Usage::Dynamic);
            gl::buffer_storage(m_glId, flags, m_size);
        }

        void bind()
        {
            gl::bind_buffer(m_glId, gl::buffer_target(S));
        }

        void copy(std::span<const T> data)
        {
            if (data.size_bytes() != m_size) throw std::runtime_error{ "Data size does not equal buffer size!" };

            copy_range(0, data);
        }
        void copy_range(u32 offset, std::span<const T> data)
        {
            if ((data.size_bytes() + (offset * sizeof(T))) > m_size) throw std::runtime_error{ "Data size exceeds buffer size!" };

            gl::buffer_sub_data(m_glId, offset * sizeof(T), data);
        }

        std::span<T> map(u32 count)
        {
            //if (count * sizeof(T) > m_size) ...
            //if (!mapped) ...
        }
        void unmap()
        {
            //glunmap...
        }

        GLuint id() const
        {
            return m_glId;
        }

    private:
        GLuint m_glId{};
    };

    template<typename T>
    class GBuffer<GraphicsAPI::OpenGL, Buffer::Type::Uniform, T> final : public Buffer
    {
    public:
        GBuffer()
            : Buffer{ sizeof(T) }
        {
            m_glId = gl::create_buffer();

            gl::buffer_storage(m_glId, Buffer::Usage::Dynamic, m_size);
        }
        GBuffer(const T& data)
            : Buffer{ sizeof(T) }
        {
            m_glId = gl::create_buffer();

            gl::buffer_storage(m_glId, Buffer::Usage::Dynamic, std::span<const T>{ &data, m_size });
        }

        void bind()
        {
            gl::bind_buffer(m_glId, Buffer::Type::Uniform);
        }

        void copy(const T& data)
        {
            gl::buffer_sub_data(m_glId, 0, std::span<const T>{ &data, m_size });
        }

        GLuint id() const
        {
            return m_glId;
        }

    private:
        GLuint m_glId{};
    };
}
