#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Buffer/IndexBuffer.hpp"

namespace hlx
{
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(unsigned int count)
            : IndexBuffer{ count }
        {
            m_internalId = OpenGL::create_index_buffer();
            OpenGL::buffer_storage(m_internalId, m_size);
        }
        OpenGLIndexBuffer(std::span<const unsigned int> data)
            : OpenGLIndexBuffer{ static_cast<unsigned int>(data.size()) }
        {
            IndexBuffer::copy(data);
        }
        ~OpenGLIndexBuffer()
        {
            OpenGL::delete_index_buffer(m_internalId);
        }

        void bind()     const override
        {
            OpenGL::bind_index_buffer(m_internalId);
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
