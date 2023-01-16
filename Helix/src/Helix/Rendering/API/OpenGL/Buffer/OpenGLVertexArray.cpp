#include "stdafx.hpp"

#include "OpenGLVertexArray.hpp"

namespace hlx
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_id);
    }
	OpenGLVertexArray::OpenGLVertexArray(std::initializer_list<std::pair<const std::shared_ptr<VertexBuffer>, const std::shared_ptr<VertexLayout>>> vertices, const std::shared_ptr<IndexBuffer> indices)
		: VertexArray{ vertices, indices }
	{
		glCreateVertexArrays(1, &m_id);

		for (const auto& [container, layout] : vertices)
		{
			tie(container, layout);
		}

		tie(m_indices);
	}
    OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_id);
	}
	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
	bool OpenGLVertexArray::is_bound() const
	{
		return false;
	}

	void OpenGLVertexArray::tie(const std::shared_ptr<VertexBuffer> vertices, const std::shared_ptr<VertexLayout> layout)
	{
		static int bindingIndex{};

		glVertexArrayVertexBuffer(m_id, bindingIndex, vertices->id(), 0, static_cast<GLsizei>(layout->stride()));

		GLint offset{};
		for (const auto& attribute : layout->attributes())
		{
			glEnableVertexArrayAttrib(m_id, m_attributeCount);
			glVertexArrayAttribFormat(m_id, m_attributeCount, attribute.count, attribute.internalType, attribute.isNormalized, offset);
			glVertexArrayAttribBinding(m_id, m_attributeCount, bindingIndex);

			offset += static_cast<GLint>(attribute.count * attribute.tSize);
			++m_attributeCount;
		}

		++bindingIndex;
	}
	void OpenGLVertexArray::tie(std::shared_ptr<IndexBuffer> indices)
	{
		glVertexArrayElementBuffer(m_id, indices->id());
	}
}
