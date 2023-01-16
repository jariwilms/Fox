#pragma once

#include "stdafx.hpp"

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Layout/VertexLayout.hpp"
#include "Helix/Core/Library/Interface/IBindable.hpp"
#include "Helix/Core/Library/Semantics/NonCopyable.hpp"

namespace hlx
{
	class VertexArray : public IBindable, public NonCopyable
	{
	public:
		virtual ~VertexArray() = default;

		virtual void tie(const std::shared_ptr<VertexBuffer> vertices, const std::shared_ptr<VertexLayout> layout) = 0;
		virtual void tie(const std::shared_ptr<IndexBuffer> indices) = 0;

	protected:
		VertexArray() = default;
		VertexArray(std::initializer_list<std::pair<const std::shared_ptr<VertexBuffer>, const std::shared_ptr<VertexLayout>>> vertices, const std::shared_ptr<IndexBuffer> indices)
			: m_vertices{ vertices }, m_indices{ indices } {}

		std::vector<std::pair<const std::shared_ptr<VertexBuffer>, const std::shared_ptr<VertexLayout>>> m_vertices{};
		std::shared_ptr<IndexBuffer> m_indices{};

		unsigned int m_attributeCount{};
	};
}
