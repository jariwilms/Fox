#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Buffer/VertexBuffer.hpp"

namespace hlx
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(size_t size)
            : VertexBuffer{ size }
        {
            m_id = OpenGL::create_vertex_buffer();
            OpenGL::buffer_storage(m_id, m_size);
        }
        template<typename T>
        OpenGLVertexBuffer(std::span<const T> data)
            : OpenGLVertexBuffer{ data.size() * sizeof(T) }
        {
            VertexBuffer::copy(data);
        }
        ~OpenGLVertexBuffer()
        {
            OpenGL::delete_vertex_buffer(m_id);
        }

        void bind() const override
        {
            OpenGL::bind_vertex_buffer(m_id);
        }

        GLuint id() const
        {
            return m_id;
        }

    protected:
        void copy(size_t size, size_t offset, const void* data) override
        {
            if (size + offset > m_size) throw std::runtime_error{ "Data size exceeds buffer size!" };
            OpenGL::buffer_sub_data(m_id, size, offset, data);
        }

    private:
        GLuint m_id{};
    };
}
