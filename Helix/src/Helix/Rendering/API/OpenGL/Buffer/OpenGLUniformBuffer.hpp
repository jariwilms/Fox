#pragma once

#include "stdafx.hpp"

#include "OpenGLBuffer.hpp"
#include "Helix/Rendering/Buffer/UniformBuffer.hpp"

namespace hlx
{
    template<typename T>
    class OpenGLUniformBuffer : public UniformBuffer<T>, public OpenGLBuffer<T>
    {
    public:
        OpenGLUniformBuffer(unsigned int binding)
            : Buffer<T>{ 1 }, UniformBuffer<T>{ binding }, OpenGLBuffer<T>{ GL_UNIFORM_BUFFER, 1 }
        {
            bind_base(m_binding);
        }
        OpenGLUniformBuffer(unsigned int binding, const T& data)
            : Buffer<T>{ 1 }, UniformBuffer<T>{ binding }, OpenGLBuffer<T>{ GL_UNIFORM_BUFFER, std::array<T, 1>{ data } } //legit
        {
            bind_base(m_binding);
        }
        ~OpenGLUniformBuffer() = default;

        void copy(const T& data) override
        {
            OpenGLBuffer<T>::copy(&data);
        }

        void bind_base(unsigned int binding) override
        {
            m_binding = binding;
            glBindBufferBase(m_internalTarget, m_binding, m_id);
        }
        void bind_range(unsigned int binding, size_t size, size_t offset) override
        {
            m_binding = binding;
            glBindBufferRange(m_internalTarget, m_binding, m_id, offset, size);
        }

    protected:
        using IBindable::m_id;
        using UniformBuffer<T>::m_binding;
        using OpenGLBuffer<T>::m_internalTarget;

        void copy_range(size_t size, size_t offset, const void* data) override
        {
            OpenGLBuffer<T>::copy_range(size, offset, data);
        }
    };
}

