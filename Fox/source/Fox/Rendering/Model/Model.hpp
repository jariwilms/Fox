#pragma once

#include <fox/rendering/material/material.hpp>
#include <fox/rendering/mesh/mesh.hpp>

import fox.core.transform;

namespace fox::gfx
{
    class Model
    {
    public:
        struct Node
        {
            Node()
                : transform{}, mesh{}, material{}, children{} {}

            fox::Transform               transform;
            std::optional<fox::uint32_t> mesh;
            std::optional<fox::uint32_t> material;
            std::vector  <fox::size_t  > children;
        };

        Model()
            : nodes{ Node{} }, meshes{}, materials{} {}

        std::vector<Node>                           nodes;
        std::vector<std::shared_ptr<gfx::Mesh    >> meshes;
        std::vector<std::shared_ptr<gfx::Material>> materials;
    };
}
