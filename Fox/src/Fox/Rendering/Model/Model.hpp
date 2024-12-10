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

            fox::Transform               localTransform{};
            std::optional<fox::uint32_t> meshIndex{};
            std::optional<fox::uint32_t> materialIndex{};
            std::vector<fox::uint32_t>   children{};
        };

        Model() = default;

        std::uint32_t                          rootNode{};
        std::vector<Node>                      nodes{};
        std::vector<std::shared_ptr<Mesh>>     meshes{};
        std::vector<std::shared_ptr<Material>> materials{};
    };
}
