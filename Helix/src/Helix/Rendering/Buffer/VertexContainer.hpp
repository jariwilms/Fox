#pragma once

#include "stdafx.hpp"

#include "Helix/Core/Library/Interface/IBindable.hpp"

namespace hlx
{
	class VertexContainer : public IBindable
	{
	public:
		enum class AccessFlag
		{
			Read       = 1,
			Write      = 2,

			Persistent = 4,
			Coherent   = 8,
		};

		virtual ~VertexContainer() = default;

		size_t size() const
		{
			return m_size;
		}

	protected:
		VertexContainer(size_t size)
			: m_size{ size } {}

        virtual void  _copy(size_t offset, size_t size, const void* data) const = 0;
        virtual void* _map(VertexContainer::AccessFlag flags) const = 0;
        virtual void  _unmap() const = 0;

		const size_t m_size{};
	};
}
