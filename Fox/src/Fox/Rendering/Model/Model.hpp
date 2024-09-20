#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/Material/Material.hpp"
#include "Fox/Rendering/Mesh/Mesh.hpp"
#include "Fox/Core/Library/Lighting/Light.hpp"
#include "Fox/Core/Library/Camera/Camera.hpp"

namespace fox::gfx
{
    class Model
    {
    public:
        Model()
            : rootNode{ std::make_unique<Node>() }
        {}

        struct Node
        {
        public:
            struct Primitive
            {
                unsigned int meshIndex{};
                unsigned int materialIndex{};
            };

            bool empty() const
            { 
                return !(localTransform.has_value() ||
                         meshPrimitive.has_value()  || 
                         cameraIndex.has_value());
            }

            std::optional<Matrix4f> localTransform{};
            std::optional<unsigned int> cameraIndex{};
            std::optional<Primitive> meshPrimitive{};

            std::vector<Node> children{};
        };

        std::unique_ptr<Node> rootNode{};
        std::vector<std::shared_ptr<Mesh>> meshes{};
        std::vector<std::shared_ptr<Light>> lights{};
        std::vector<std::shared_ptr<Camera>> cameras{};
        std::vector<std::shared_ptr<Material>> materials{};
    };
}
