#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/Using.hpp"

namespace fox::gfx
{
    class Material
    {
    public:
        Material(const std::string& name)
            : name{ name } {}

        std::string name{};

        fox::Vector4f color{};
        float roughness{};
        float metallic{};

        std::shared_ptr<const gfx::Texture2D> albedoMap{};
        std::shared_ptr<const gfx::Texture2D> normalMap{};
        std::shared_ptr<const gfx::Texture2D> armMap{};
        std::shared_ptr<const gfx::Texture2D> emissionMap{};
    };
}
