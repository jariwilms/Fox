#pragma once

#include "stdafx.hpp"

#include "Buffer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Helix/Rendering/Layout/VertexLayout.hpp"
#include "Helix/Rendering/Interface/IBindable.hpp"

namespace hlx
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;

        virtual void bind()     const = 0;
        virtual void unbind()   const = 0;
        virtual bool is_bound() const = 0;

        template<typename T>
        void tie(const std::shared_ptr<Buffer<T>> vertices, const std::shared_ptr<VertexLayout> layout)
        {
            tie(0, layout);
        }
        virtual void tie(const std::shared_ptr<IndexBuffer> indices) = 0;

        bool indexed() const
        {
            return m_indices != nullptr;
        }

        const std::shared_ptr<const IndexBuffer> indices() const
        {
            return m_indices;
        }

    protected:
        VertexArray() = default;

        virtual void tie(Id bufferId, const std::shared_ptr<VertexLayout> layout) = 0;

        std::shared_ptr<const IndexBuffer> m_indices{};
        unsigned int m_attributes{};
    };
}
