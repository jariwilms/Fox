//#pragma once
//
//#include "stdafx.hpp"
//
//#include "Layout/VertexLayout.hpp"
//#include "VertexContainer.hpp"
//
//namespace hlx
//{
//	template<typename T>
//	class VertexBuffer : public VertexContainer
//	{
//	public:
//		VertexBuffer(const VertexBuffer<T>& other) = delete;
//		virtual ~VertexBuffer() = default;
//
//		static std::shared_ptr<VertexBuffer<T>> create(unsigned int count);
//		static std::shared_ptr<VertexBuffer<T>> create(unsigned int count, const std::span<T>& data);
//
//		virtual void copy(unsigned int offset, const std::span<T>& data) const = 0;
//		virtual std::weak_ptr<std::span<T>> map(VertexContainer::AccessFlag access) const = 0;
//		virtual std::weak_ptr<std::span<T>> map(unsigned int offset, unsigned int count, VertexContainer::AccessFlag access) const = 0;
//		virtual void unmap() const = 0;
//
//		VertexBuffer<T>& operator=(const VertexBuffer<T>& other) = delete;
//
//	protected:
//		VertexBuffer(unsigned int count);
//	};
//}
