#pragma once

#include <fox/core/types/transform/transform.hpp>
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

            fox::Transform               localTransform{};
            std::optional<fox::uint32_t> meshIndex{};
            std::optional<fox::uint32_t> materialIndex{};
            std::vector<fox::uint32_t>   children{};
        };

        Model() = default;

        std::uint32_t                               rootNode{};
        std::vector<Node>                           nodes{};
        std::vector<std::shared_ptr<gfx::Mesh>>     meshes{};
        std::vector<std::shared_ptr<gfx::Material>> materials{};
    };
}
