#pragma once

#include "stdafx.hpp"

#include "Buffer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Helix/Rendering/Layout/VertexLayout.hpp"
#include "Helix/Rendering/Interface/IBindable.hpp"

namespace hlx
{
    class VertexArray : public IBindable
    {
    public:
        virtual ~VertexArray() = default;

        template<typename T>
        void tie(const std::shared_ptr<Buffer<T>> vertices, const std::shared_ptr<VertexLayout> layout)
        {
            tie(vertices->id(), layout);
        }
        virtual void tie(const std::shared_ptr<IndexBuffer> indices) = 0;

        const std::shared_ptr<const IndexBuffer> indices() const
        {
            return m_indices;
        }
        bool indexed() const
        {
            return m_indices != nullptr;
        }

    protected:
        VertexArray() = default;

        virtual void tie(Id bufferId, const std::shared_ptr<VertexLayout> layout) = 0;

        std::shared_ptr<const IndexBuffer> m_indices{};
        unsigned int m_attributes{};
    };
}
