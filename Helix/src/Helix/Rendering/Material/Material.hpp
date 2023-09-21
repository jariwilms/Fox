#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Texture/Texture2D.hpp"
#include "Helix/Rendering/Shader/Pipeline.hpp"

namespace hlx
{
    class Material
    {
    public:
        Material(const std::string& name)
            : name{ name } {}

        std::string name{};

        Vector4f color{};
        float roughness{};
        float metallic{};

        std::shared_ptr<const Texture2D> albedoMap{};
        std::shared_ptr<const Texture2D> normalMap{};
        std::shared_ptr<const Texture2D> armMap{};
        std::shared_ptr<const Texture2D> emissionMap{};
    };
}
