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
    class TestModel
    {
    public:
        struct Node
        {
            Transform transform{};
            std::shared_ptr<Mesh> mesh{};
            CameraComponent camera{};

            std::vector<Node> children{};
        };

        TestModel() = default;

        void build_from_root()
        {

        }

        Node rootNode{};
        std::vector<std::shared_ptr<Mesh>> meshes{};
        std::vector<std::shared_ptr<LightComponent>> lights{};
        std::vector<std::shared_ptr<Material>> materials{};

        std::unordered_map<std::shared_ptr<Mesh>, std::shared_ptr<DefaultMaterial>> materialMap{};
        std::unordered_map<std::shared_ptr<DefaultMaterial>, std::vector<std::shared_ptr<Mesh>>> meshMap{};
    };
}
