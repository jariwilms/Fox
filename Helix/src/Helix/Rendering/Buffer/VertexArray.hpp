#pragma once

#include "stdafx.hpp"

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Helix/Rendering/Layout/VertexLayout.hpp"

namespace hlx
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;

        virtual void bind() const = 0;

        virtual void tie(const std::shared_ptr<VertexBuffer> vertexBuffer, const std::shared_ptr<VertexLayout> vertexLayout) = 0;
        virtual void tie(const std::shared_ptr<IndexBuffer>  indexBuffer) = 0;

        virtual unsigned int primitive_count() const = 0;
        virtual bool indexed() const = 0;

        virtual const std::shared_ptr<const IndexBuffer> index_buffer() const = 0;

    protected:
        VertexArray() = default;
    };
}
