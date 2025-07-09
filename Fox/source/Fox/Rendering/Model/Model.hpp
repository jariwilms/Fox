#pragma once

#include <fox/core/transform/transform.hpp>
#include <fox/rendering/material/material.hpp>
#include <fox/rendering/mesh/mesh.hpp>

namespace fox::gfx
{
    class Model
    {
    public:
        struct Node
        {
            Node() = default;

            fox::Transform               transform;
            std::optional<fox::uint32_t> mesh;
            std::optional<fox::uint32_t> material;
            std::vector  <fox::size_t  > children;
        };

        Model()
            : root{} {}

        std::uint32_t                               root;
        std::vector<Node>                           nodes;
        std::vector<std::shared_ptr<gfx::Mesh    >> meshes;
        std::vector<std::shared_ptr<gfx::Material>> materials;
    };
}
