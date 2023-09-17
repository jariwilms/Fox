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
            m_internalTarget = GL_UNIFORM_BUFFER;
            glCreateBuffers(1, &m_internalId);

            bind(m_binding);
        }
        OpenGLUniformBuffer(unsigned int binding, const T& data)
            : OpenGLUniformBuffer{ binding }
        {
            UniformBuffer<T>::copy(data);
        }
        ~OpenGLUniformBuffer() = default;

        void bind(unsigned int binding) override
        {
            m_binding = binding;
            glBindBufferBase(m_internalTarget, m_binding, m_internalId);
        }

    protected:
        void copy(size_t size, size_t offset, const void* data) override
        {
            if (size + offset > m_size) throw std::invalid_argument{ "Data exceeds buffer size!" };

            glNamedBufferSubData(m_internalId, offset, size, data);
        }

    private:
        using Buffer::m_size;
        using UniformBuffer<T>::m_binding;

        GLuint m_internalId{};
        GLuint m_internalTarget{};

        //static inline std::unordered_map<unsigned int, GLuint> s_bindingToIdMap{};
    };
}

