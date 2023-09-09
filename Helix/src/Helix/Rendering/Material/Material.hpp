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
        Material(const Material& other) = default;

        std::string name{};

        Vector3f color{ 1.0f, 1.0f, 1.0f };

        std::shared_ptr<Texture2D> albedoMap{};
        std::shared_ptr<Texture2D> normalMap{};
        std::shared_ptr<Texture2D> metallicMap{};

        float metallic{ 0.0f };
        float roughness{ 0.0f };
    };
}
