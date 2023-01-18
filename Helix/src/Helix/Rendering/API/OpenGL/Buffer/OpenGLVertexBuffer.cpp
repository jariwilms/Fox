#include "stdafx.hpp"

#include "OpenGLVertexBuffer.hpp"

namespace hlx
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size)
        : VertexBuffer{ size }
    {
        glCreateBuffers(1, &m_id);
        glNamedBufferStorage(m_id, m_size, nullptr, GL_DYNAMIC_STORAGE_BIT);
    }
    OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size, const void* data)
        : VertexBuffer{ size }
    {
        glCreateBuffers(1, &m_id);
        glNamedBufferStorage(m_id, m_size, data, GL_DYNAMIC_STORAGE_BIT);
    }
    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    void OpenGLVertexBuffer::bind() const 
    {
        if (m_isMapped) throw std::runtime_error{ "Buffer may not be mapped while rendering!" };

        glBindBuffer(m_internalTarget, m_id);
    }
    void OpenGLVertexBuffer::unbind() const
    {
        glBindBuffer(m_internalTarget, 0);
    }
    bool OpenGLVertexBuffer::is_bound() const
    {
        return false;
    }

    void  OpenGLVertexBuffer::_copy(size_t offset, size_t size, const void* data) const
    {
        if (!data) return;
        if (offset + size > m_size) throw std::range_error{ "Vertices exceed container size!" };

        glNamedBufferSubData(m_id, offset, size, data);
    }
    void* OpenGLVertexBuffer::_map(VertexContainer::AccessFlag flags) const
    {
        return glMapNamedBuffer(m_id, OpenGL::buffer_access(flags));
    }
    void  OpenGLVertexBuffer::_unmap() const
    {
        glUnmapNamedBuffer(m_id);
    }
}
