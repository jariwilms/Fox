#pragma once

#include "stdafx.hpp"

#include "OpenGLBuffer.hpp"
#include "Helix/Rendering/Buffer/UniformArrayBuffer.hpp"

namespace hlx
{
    //enum Binding : unsigned int;

    //void a(Binding binding)
    //{

    //}
    //void b()
    //{
    //    a(Binding{ 2u });
    //    a(2u);
    //}

    template<typename T>
    class OpenGLUniformArrayBuffer : public UniformArrayBuffer<T>, public OpenGLBuffer<T>
    {
    public:
        OpenGLUniformArrayBuffer(unsigned int count, unsigned int binding)     //TODO: specify binding before count?
            : Buffer<T>{ count }, UniformArrayBuffer<T>{ count, binding }, OpenGLBuffer<T>{ GL_UNIFORM_BUFFER, count }
        {
            bind_base(m_binding);
        }
        OpenGLUniformArrayBuffer(unsigned int binding, std::span<const T> data)
            : Buffer<T>{ static_cast<unsigned int>(data.size()) }, UniformArrayBuffer<T>{ static_cast<unsigned int>(data.size()), binding }, OpenGLBuffer<T>{ GL_UNIFORM_BUFFER, data }
        {
            bind_base(m_binding);
        }
        ~OpenGLUniformArrayBuffer() = default;

        void copy(std::span<const T> data) override
        {
            OpenGLBuffer<T>::copy(data.data());
        }
        void copy_index(unsigned int index, const T& data) override
        {
            copy_range(sizeof(T), index * sizeof(T), &data);
        }
        void copy_index_range(unsigned int index, std::span<const T> data) override
        {
            copy_range(data.size() * sizeof(T), index * sizeof(T), data.data());
        }

        void bind_base(unsigned int binding) override
        {
            m_binding = binding;
            glBindBufferBase(m_internalTarget, m_binding, m_id);
        }
        void bind_range(unsigned int count, unsigned int binding, unsigned int index, size_t offset) override
        {
            m_binding = binding;
            glBindBufferRange(m_internalTarget, m_binding, m_id, index * sizeof(T) + offset, count * sizeof(T));
        }

    protected:
        using IBindable::m_id;
        using UniformArrayBuffer<T>::m_binding;
        using OpenGLBuffer<T>::m_internalTarget;

        void copy_range(size_t size, size_t offset, const void* data) override
        {
            OpenGLBuffer<T>::copy_range(size, offset, data);
        }
    };
}
