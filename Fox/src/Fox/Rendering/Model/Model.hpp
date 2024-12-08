#pragma once

#include "stdafx.hpp"

#include "Fox/Core/Library/Camera/Camera.hpp"
#include "Fox/Core/Library/Lighting/Light.hpp"
#include "Fox/Core/Library/Transform/Transform.hpp"
#include "Fox/Rendering/Material/Material.hpp"
#include "Fox/Rendering/Mesh/Mesh.hpp"

namespace fox::gfx
{
    class Model
    {
    public:
        struct Node
        {
            Node() = default;

            std::optional<fox::uint32_t> meshIndex{};
            std::optional<fox::uint32_t> materialIndex{};
            fox::Transform               localTransform{};
            std::vector<Node>            children{};
        };

        Model()
            : root{ std::make_unique<Node>() } 
        {}

        void traverse(const Node& node, std::function<void(const Node&)> function) const
        {
            function(node);

            for (const auto& child : node.children)
            {
                traverse(child, function);
            }
        }

        std::unique_ptr<Node>                  root{};
        std::vector<std::shared_ptr<Mesh>>     meshes{};
        std::vector<std::shared_ptr<Material>> materials{};
    };
}
