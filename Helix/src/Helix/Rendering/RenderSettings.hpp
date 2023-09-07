#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Texture/CubemapTexture.hpp"

namespace hlx
{
    class RenderSettings
    {
    public:
        struct Lighting
        {
            Vector3f ambientColor{ 1.0f, 1.0f, 1.0f };
            float ambientMultiplier{ 1.0f };
            std::shared_ptr<CubemapTexture> skybox{};
        };

        static inline Lighting lighting{};
    };
}
