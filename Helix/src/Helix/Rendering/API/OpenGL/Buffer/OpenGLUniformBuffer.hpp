#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Buffer/UniformBuffer.hpp"

namespace hlx
{
    template<typename T>
    class OpenGLUniformBuffer : public UniformBuffer<T>
    {
    public:
        OpenGLUniformBuffer(unsigned int binding)
            : UniformBuffer<T>{ binding }
        {
            m_id = OpenGL::create_buffer();
            OpenGL::buffer_storage(m_id, sizeof(T));

            bind(m_binding);
        }
        OpenGLUniformBuffer(unsigned int binding, const T& data)
            : OpenGLUniformBuffer{ binding }
        {
            UniformBuffer<T>::copy(data);
        }
        ~OpenGLUniformBuffer()
        {
            OpenGL::delete_buffer(m_id);
        }

        void bind(unsigned int binding) override
        {
            m_binding = binding;
            OpenGL::bind_buffer_base(m_id, m_binding, GL_UNIFORM_BUFFER);
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
        using UniformBuffer<T>::m_binding;

        GLuint m_id{};
    };
}

