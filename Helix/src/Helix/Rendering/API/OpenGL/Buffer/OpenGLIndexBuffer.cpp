#include "stdafx.hpp"

#include "OpenGLIndexBuffer.hpp"

namespace hlx
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(size_t size)
		: IndexBuffer{ size }
	{
		glCreateBuffers(1, &m_id);
		glNamedBufferStorage(m_id, m_size, nullptr, GL_DYNAMIC_STORAGE_BIT);
	}
	OpenGLIndexBuffer::OpenGLIndexBuffer(size_t size, const void* data)
		: IndexBuffer{ size }
	{
        glCreateBuffers(1, &m_id);
        glNamedBufferStorage(m_id, m_size, data, GL_DYNAMIC_STORAGE_BIT);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void OpenGLIndexBuffer::bind() const
	{
        if (!m_mappedBuffer.expired()) throw std::runtime_error{ "Buffer may not be mapped while rendering!" };

		glBindBuffer(m_target, m_id);
	}
	void OpenGLIndexBuffer::unbind() const
	{
		glBindBuffer(m_target, 0);
	}
	bool OpenGLIndexBuffer::is_bound() const
	{
		return false;
	}

	void  OpenGLIndexBuffer::_copy(size_t offset, size_t size, const void* data) const
	{
		if (!data) return;
		if (offset + size > m_size) throw std::range_error{ "Indices exceed container size!" };

		glNamedBufferSubData(m_id, offset, size, data);
	}
	void* OpenGLIndexBuffer::_map(VertexContainer::AccessFlag flags) const
	{
		return glMapNamedBuffer(m_id, OpenGL::buffer_access(flags));
	}
	void  OpenGLIndexBuffer::_unmap() const
	{
        glUnmapNamedBuffer(m_id);
	}
}
