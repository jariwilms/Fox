#pragma once

#include "stdafx.hpp"

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

        virtual void tie(const std::shared_ptr<VertexBuffer> vertices, const std::shared_ptr<VertexLayout> layout) = 0;
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

        std::shared_ptr<const IndexBuffer> m_indices{};
        unsigned int m_attributes{};
    };
}
