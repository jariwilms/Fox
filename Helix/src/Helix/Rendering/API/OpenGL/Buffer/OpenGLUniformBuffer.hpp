#pragma once

#include "stdafx.hpp"

#include "OpenGLBuffer.hpp"
#include "Helix/Rendering/Buffer/UniformBuffer.hpp"

namespace hlx
{
    template<typename T>
    class OpenGLUniformBuffer : public OpenGLBuffer<T>, public UniformBuffer<T>
    {
    public:
        OpenGLUniformBuffer()
            : OpenGLBuffer<T>{ GL_UNIFORM_BUFFER, 1 }, UniformBuffer<T>{ 1 }, Buffer<T>{ 1 } {}
        OpenGLUniformBuffer(const T& data)
            : OpenGLBuffer<T>{ GL_UNIFORM_BUFFER, 1 }, UniformBuffer<T>{ 1 }, Buffer<T>{ 1 }
        {
            OpenGLBuffer<T>::copy(&data);
        }
        ~OpenGLUniformBuffer() = default;

        void bind_base(unsigned int index) override
        {
            glBindBufferBase(m_internalTarget, index, m_id);
        }
        void bind_range(unsigned int index, size_t size, size_t offset) override
        {
            glBindBufferRange(m_internalTarget, index, m_id, offset, size);
        }

    protected:
        using IBindable::m_id;
        using OpenGLBuffer<T>::m_internalTarget;
    };
}

