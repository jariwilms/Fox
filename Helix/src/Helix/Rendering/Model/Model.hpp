#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Mesh/Mesh.hpp"

namespace hlx
{
    class Model
    {
    public:
        Model() = default;

        std::vector<std::shared_ptr<Mesh>> meshes{};
        std::vector<std::shared_ptr<DefaultMaterial>> materials{};

        std::unordered_map<std::shared_ptr<Mesh>, std::shared_ptr<DefaultMaterial>> materialMap{};
        std::unordered_map<std::shared_ptr<DefaultMaterial>, std::vector<std::shared_ptr<Mesh>>> meshMap{};
    };
}
