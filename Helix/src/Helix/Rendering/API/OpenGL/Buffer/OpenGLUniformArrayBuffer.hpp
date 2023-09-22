#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Buffer/UniformArrayBuffer.hpp"

namespace hlx
{
    template<typename T>
    class OpenGLUniformArrayBuffer : public UniformArrayBuffer<T>
    {
    public:
        OpenGLUniformArrayBuffer(unsigned int binding, unsigned int count)
            : UniformArrayBuffer<T>{ binding, count }
        {
            m_id = OpenGL::create_buffer();
            OpenGL::buffer_storage(m_id, count * sizeof(T));

            bind(m_binding);
        }
        OpenGLUniformArrayBuffer(unsigned int binding, std::span<const T> data)
            : OpenGLUniformArrayBuffer{ binding, data.size() }
        {
            UniformArrayBuffer<T>::copy(data);
        }
        ~OpenGLUniformArrayBuffer()
        {
            OpenGL::delete_buffer(m_id);
        }

        void bind(unsigned int binding) override
        {
            m_binding = binding;
            OpenGL::bind_buffer_base(m_id, m_binding, GL_UNIFORM_BUFFER);
        }
        void bind_range(unsigned int binding, unsigned int index, unsigned int count) override
        {
            m_binding = binding;
            OpenGL::bind_buffer_range(m_id, m_binding, GL_UNIFORM_BUFFER, index * sizeof(T), count * sizeof(T));
        }

        GLuint id() const
        {
            return m_id;
        }

    protected:
        void copy(size_t size, size_t offset, const void* data) override
        {
            if (size + offset > m_size) throw std::invalid_argument{ "Data exceeds buffer size!" };

            OpenGL::buffer_sub_data(m_id, size, offset, data);
        }

    private:
        using Buffer::m_size;
        using UniformArrayBuffer<T>::m_binding;

        GLuint m_id{};
    };
}
