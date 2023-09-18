#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Buffer/UniformArrayBuffer.hpp"

namespace hlx
{
    template<typename T>
    class OpenGLUniformArrayBuffer : public UniformArrayBuffer<T>
    {
    public:
        OpenGLUniformArrayBuffer(unsigned int binding, unsigned int count)     //TODO: specify binding before count?
            : UniformArrayBuffer<T>{ binding, count }
        {
            m_internalTarget = GL_UNIFORM_BUFFER;
            glCreateBuffers(1, &m_internalId);
            glNamedBufferStorage(m_internalId, count * sizeof(T), nullptr, GL_DYNAMIC_STORAGE_BIT);

            bind(m_binding);
        }
        OpenGLUniformArrayBuffer(unsigned int binding, std::span<const T> data)
            : OpenGLUniformArrayBuffer{ binding, data.size() }
        {
            UniformArrayBuffer<T>::copy(data);
        }
        ~OpenGLUniformArrayBuffer() = default;

        void bind(unsigned int binding) override
        {
            m_binding = binding;
            glBindBufferBase(m_internalTarget, m_binding, m_internalId);
        }
        void bind_range(unsigned int binding, unsigned int index, unsigned int count) override
        {
            m_binding = binding;
            glBindBufferRange(m_internalTarget, binding, m_internalId, index * sizeof(T), count * sizeof(T));
        }

    protected:
        void copy(size_t size, size_t offset, const void* data) override
        {
            if (size + offset > m_size) throw std::invalid_argument{ "Data exceeds buffer size!" };

            glNamedBufferSubData(m_internalId, offset, size, data);
        }

    private:
        using Buffer::m_size;
        using UniformArrayBuffer<T>::m_binding;

        GLuint m_internalId{};
        GLuint m_internalTarget{};
    };
}
