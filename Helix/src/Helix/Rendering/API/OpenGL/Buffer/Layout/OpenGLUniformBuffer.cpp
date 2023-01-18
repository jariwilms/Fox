#include "stdafx.hpp"

#include "OpenGLUniformBuffer.hpp"

namespace hlx
{
    OpenGLUniformBuffer::OpenGLUniformBuffer(size_t size)
        : UniformBuffer{ size }
    {
        glCreateBuffers(1, &m_id);
        glNamedBufferStorage(m_id, m_size, nullptr, GL_DYNAMIC_STORAGE_BIT);
    }
    OpenGLUniformBuffer::OpenGLUniformBuffer(size_t size, const void* data)
        : UniformBuffer{ size }
    {
        glCreateBuffers(1, &m_id);
        glNamedBufferStorage(m_id, m_size, data, GL_DYNAMIC_STORAGE_BIT);
    }
    OpenGLUniformBuffer::~OpenGLUniformBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    void OpenGLUniformBuffer::bind() const
    {
        glBindBuffer(m_internalTarget, m_id);
    }
    void OpenGLUniformBuffer::bind_base(unsigned int index)
    {
        glBindBufferBase(m_internalTarget, index, m_id);
    }
    void OpenGLUniformBuffer::bind_range(unsigned int index, size_t size, size_t offset)
    {
        glBindBufferRange(m_internalTarget, index, m_id, offset, size);
    }
    void OpenGLUniformBuffer::unbind() const
    {
        glBindBuffer(m_internalTarget, 0);
    }
    bool OpenGLUniformBuffer::is_bound() const
    {
        return false;
    }

    void OpenGLUniformBuffer::_copy(size_t size, size_t offset, const void* data)
    {
        glNamedBufferSubData(m_id, offset, size, data);
    }
}
