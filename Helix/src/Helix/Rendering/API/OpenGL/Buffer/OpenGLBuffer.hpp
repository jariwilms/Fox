#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Buffer/Buffer.hpp"

namespace hlx
{
    template<typename T>
    class OpenGLBuffer : public virtual Buffer<T>
    {
    public:
        OpenGLBuffer(GLenum target, unsigned int count)
            : Buffer<T>{ count }, m_internalTarget{ target }
        {
            glCreateBuffers(1, &m_id);
            glNamedBufferStorage(m_id, m_size, nullptr, GL_DYNAMIC_STORAGE_BIT);
        }
        OpenGLBuffer(GLenum target, const std::span<T>& data)
            : Buffer<T>{ static_cast<unsigned int>(data.size()) }, m_internalTarget{ target }
        {
            glCreateBuffers(1, &m_id);
            glNamedBufferStorage(m_id, m_size, data.data(), GL_DYNAMIC_STORAGE_BIT);
        }
        virtual ~OpenGLBuffer()
        {
            glDeleteBuffers(1, &m_id);
        }

        void bind() const override
        {
            glBindBuffer(m_internalTarget, m_id);
        }
        void unbind() const override
        {
            glBindBuffer(m_internalTarget, 0);
        }
        bool is_bound() const override
        {
            return false;
        }

    protected:
        using IBindable::m_id;
        using Buffer<T>::m_size;

        void copy(const void* data) override
        {
            glNamedBufferSubData(m_id, 0, m_size, data);
        }
        void copy_range(size_t size, size_t offset, const void* data) override
        {
            glNamedBufferSubData(m_id, offset, size, data);
        }

        GLenum m_internalTarget{};
    };
}
