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
        OpenGLBuffer(GLenum target, unsigned int tCount)
            : Buffer<T>{ tCount }, m_internalTarget{ target }
        {
            glCreateBuffers(1, &m_internalId);
            glNamedBufferStorage(m_internalId, m_size, nullptr, GL_DYNAMIC_STORAGE_BIT);
        }
        OpenGLBuffer(GLenum target, std::span<const T> data)
            : Buffer<T>{ static_cast<unsigned int>(data.size()) }, m_internalTarget{ target }
        {
            glCreateBuffers(1, &m_internalId);
            glNamedBufferStorage(m_internalId, m_size, data.data(), GL_DYNAMIC_STORAGE_BIT);
        }
        virtual ~OpenGLBuffer()
        {
            glDeleteBuffers(1, &m_internalId);
        }

        void bind()     const override
        {
            glBindBuffer(m_internalTarget, m_internalId);
        }
        void unbind()   const override
        {
            glBindBuffer(m_internalTarget, 0);
        }
        bool is_bound() const override
        {
            throw std::runtime_error{ "Method has not been implemented!" };
        }

        GLuint internal_id()     const
        {
            return m_internalId;
        }
        GLenum internal_target() const
        {
            return m_internalTarget;
        }

    protected:
        using Buffer<T>::m_size;

        void copy(const void* data) override
        {
            glNamedBufferSubData(m_internalId, 0, m_size, data);
        }
        void copy_range(size_t size, size_t offset, const void* data) override
        {
            glNamedBufferSubData(m_internalId, offset, size, data);
        }

        GLuint m_internalId{};
        GLenum m_internalTarget{};
    };
}
