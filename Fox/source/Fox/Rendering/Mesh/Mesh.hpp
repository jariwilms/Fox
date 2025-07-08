#pragma once

#include <fox/rendering/buffer/vertex_array.hpp>

namespace fox::gfx
{
    struct Mesh
    {
    public:
        Mesh(std::shared_ptr<const gfx::VertexArray> vertexArray)
            : vertexArray{ vertexArray } {}

        void bind       () const
        {
            vertexArray->bind();
        }
        auto index_count() const -> fox::count_t
        {
            return vertexArray->index_count();
        }

    private:
        std::shared_ptr<const gfx::VertexArray> vertexArray;
    };
}
