#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/Using.hpp"

namespace fox::gfx
{
    class Material
    {
    public:
        Material(const std::string& name = {})
            : name{ name } {}

        std::string name{};

        fox::Vector4f  color{};
        fox::float32_t roughnessFactor{};
        fox::float32_t metallicFactor{};

        std::shared_ptr<const gfx::Texture2D> albedo{};
        std::shared_ptr<const gfx::Texture2D> normal{};
        std::shared_ptr<const gfx::Texture2D> arm{};
        std::shared_ptr<const gfx::Texture2D> emission{};
    };
}
