//#pragma once
//
//#include "stdafx.hpp"
//
//#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
//#include "Helix/Rendering/Buffer/VertexBuffer.hpp"
//
//namespace hlx
//{
//	class OpenGLVertexBuffer : public VertexBuffer
//	{
//	public:
//		OpenGLVertexBuffer(size_t size);
//		OpenGLVertexBuffer(size_t size, const void* data);
//		~OpenGLVertexBuffer() override;
//
//		void bind() const override;
//		void unbind() const override;
//		bool is_bound() const override;
//
//	private:
//        void  _copy(size_t offset, size_t size, const void* data) const override;
//        void* _map(VertexContainer::AccessFlag flags) const override;
//        void  _unmap() const override;
//
//		GLenum m_internalTarget{ GL_ARRAY_BUFFER };
//	};
//}
