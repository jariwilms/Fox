#pragma once

#include "stdafx.hpp"

#include "Component.hpp"

namespace hlx
{
    struct MeshRenderer : public Component
    {
    public:
        struct LightingOptions
        {
            enum class ShadowCasting
            {
                On, 
                Off, 
                Two_Sided, 
                Shadows_Only, 
            };

            LightingOptions() = default;

            ShadowCasting shadowCasting{ ShadowCasting::On };
            bool receiveShadows{ true };
        };

        MeshRenderer()
        {

        }

        //std::shared_ptr<Material> material{};
        LightingOptions lightingOptions{};
    };
}
