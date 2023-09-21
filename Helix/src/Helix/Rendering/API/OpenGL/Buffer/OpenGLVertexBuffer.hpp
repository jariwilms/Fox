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
            m_internalId = OpenGL::create_vertex_buffer();
            OpenGL::buffer_storage(m_internalId, m_size);
        }
        template<typename T>
        OpenGLVertexBuffer(std::span<const T> data)
            : OpenGLVertexBuffer{ data.size() * sizeof(T) }
        {
            VertexBuffer::copy(data);
        }
        ~OpenGLVertexBuffer()
        {
            OpenGL::delete_vertex_buffer(m_internalId);
        }

        void bind() const override
        {
            OpenGL::bind_vertex_buffer(m_internalId);
        }

        GLuint internal_id()     const
        {
            return m_internalId;
        }

    protected:
        void copy(size_t size, size_t offset, const void* data) override
        {
            if (size + offset > m_size) throw std::runtime_error{ "Data size exceeds buffer size!" };
            OpenGL::buffer_sub_data(m_internalId, size, offset, data);
        }

    private:
        GLuint m_internalId{};
    };
}
