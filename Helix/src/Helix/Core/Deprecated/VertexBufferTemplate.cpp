#include "stdafx.hpp"
//
//#include "VertexBuffer.hpp"
//#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLVertexBuffer.hpp"
//
//namespace hlx
//{
//	template<typename T>
//	std::shared_ptr<VertexBuffer<T>> VertexBuffer<T>::create(unsigned int count)
//	{
//		return std::make_shared<OpenGLVertexBuffer<T>>(count);
//	}
//	template<typename T>
//	std::shared_ptr<VertexBuffer<T>> VertexBuffer<T>::create(unsigned int count, const std::span<T>& data)
//	{
//		return std::make_shared<OpenGLVertexBuffer<T>>(count, data);
//	}
//
//	template<typename T>
//    VertexBuffer<T>::VertexBuffer(unsigned int count)
//		: VertexContainer{ count, sizeof(T) }
//    {
//        if (!count) throw std::invalid_argument{ "Buffer size must be greater than 0!" };
//    }
//}
