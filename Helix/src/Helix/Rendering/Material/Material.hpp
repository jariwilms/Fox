#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Texture/Texture2D.hpp"

namespace hlx
{
    class Material
    {
    public:
        Material() = default;

        std::string name{ "Default" };

        Vector4u color{ 1.0f, 1.0f, 1.0f, 1.0f };
        std::shared_ptr<Texture2D> albedo{};
        std::shared_ptr<Texture2D> normal{};
        float metallic{ 0.0f };
        float roughness{ 0.0f };

        bool operator==(const Material& other)
        {
            return
                color     == other.color     &&
                metallic  == other.metallic  &&
                roughness == other.roughness &&
                albedo    == other.albedo    &&
                normal    == other.normal     ;
        }
    };
}
