#pragma once

#include "stdafx.hpp"

#include "VertexAttribute.hpp"

namespace hlx
{
	class VertexLayout
	{
	public:
		VertexLayout() = default;

		template<typename T>
		void specify(unsigned int count)
		{
			const auto& typeId = typeid(T);
			const auto& typeHash = typeId.hash_code();

			m_attributes.emplace_back(count, typeHash);
			m_stride += count * sizeof(T);
		}

		const std::vector<VertexAttribute>& attributes() const
		{
			return m_attributes;
		}
		size_t stride() const
		{
			return m_stride;
		}

	private:
		std::vector<VertexAttribute> m_attributes{};
		size_t m_stride{};
	};
}
