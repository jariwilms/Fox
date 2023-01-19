//#pragma once
//
//#include "stdafx.hpp"
//
//#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
//#include "Helix/Rendering/Buffer/VertexArray.hpp"
//
//namespace hlx
//{
//	class OpenGLVertexArray : public VertexArray
//	{
//	public:
//		OpenGLVertexArray();
//		OpenGLVertexArray(std::initializer_list<std::pair<const std::shared_ptr<VertexBuffer>, const std::shared_ptr<VertexLayout>>> vertices, const std::shared_ptr<IndexBuffer> indices);
//		~OpenGLVertexArray() override;
//
//		void bind() const override;
//		void unbind() const override;
//		bool is_bound() const override;
//
//		void tie(const std::shared_ptr<VertexBuffer> vertices, const std::shared_ptr<VertexLayout> layout) override;
//        void tie(const std::shared_ptr<IndexBuffer> indices) override;
//	};
//}
