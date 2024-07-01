#pragma once

#include "stdafx.hpp"

#include "Component.hpp"

#include "Fox/Rendering/Mesh/Mesh.hpp"
#include "Fox/Rendering/Material/Material.hpp"

namespace fox
{
    struct MeshRendererComponent : public Component
    {
    public:
        MeshRendererComponent(Entity& parent)
            : Component{ parent } {}

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
            unsigned int maxShadowCastingLights{ 8 }; //TODO: global config setting
            bool receiveShadows{ true };
        };

        std::shared_ptr<gfx::Mesh> mesh{};
        std::shared_ptr<gfx::Material> material{};
        //LightingOptions lightingOptions{};
    };
}
