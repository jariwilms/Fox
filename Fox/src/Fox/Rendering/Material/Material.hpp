#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/Using.hpp"

namespace fox::gfx
{
    struct Material
    {
    public:
        std::string name{ "Material" };

        fox::Vector4f  color{ 1.0f };
        fox::float32_t roughnessFactor{ 0.5f };
        fox::float32_t metallicFactor{ 0.0f };

        std::shared_ptr<const gfx::Texture2D> albedo{};
        std::shared_ptr<const gfx::Texture2D> normal{};
        std::shared_ptr<const gfx::Texture2D> arm{};
        std::shared_ptr<const gfx::Texture2D> emissive{};
    };
}
