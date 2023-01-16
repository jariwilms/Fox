#pragma once

#include "stdafx.hpp"

#include "VertexContainer.hpp"
#include "Helix/Core/Library/Semantics/NonCopyable.hpp"

namespace hlx
{
	class IndexBuffer : public VertexContainer, public NonCopyable
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void copy(size_t offset, const std::span<unsigned int>& data)
		{
			_copy(offset, data.size() * sizeof(unsigned int), data.data());
		}
		virtual std::weak_ptr<std::span<unsigned int>> map(VertexContainer::AccessFlag flags)
		{
			auto* buffer = reinterpret_cast<unsigned int*>(_map(flags));
			m_isMapped = true;

			return std::make_shared<std::span<unsigned int>>(buffer, m_size / sizeof(unsigned int));
		}
		virtual void unmap()
		{
			m_mappedBuffer.reset();
			_unmap();
		}

	protected:
		IndexBuffer(size_t size)
			: VertexContainer{ size } {}

		bool m_isMapped{};
	};
}
