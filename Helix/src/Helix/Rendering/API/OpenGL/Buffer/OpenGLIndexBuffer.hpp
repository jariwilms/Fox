#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Buffer/IndexBuffer.hpp"

namespace hlx
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(size_t size);
		OpenGLIndexBuffer(size_t size, const void* data);
		~OpenGLIndexBuffer();

		void bind() const override;
		void unbind() const override;
		bool is_bound() const override;

	private:
		void  _copy(size_t offset, size_t size, const void* data) const override;
		void* _map(VertexContainer::AccessFlag flags) const override;
		void  _unmap() const override;

		OpenGL::Target m_target{ GL_ELEMENT_ARRAY_BUFFER };
	};
}
