#pragma once

#include "stdafx.hpp"

#include "Fox/ECS/Components/Component.hpp"
#include "Fox/Rendering/Mesh/Mesh.hpp"
#include "Fox/Rendering/Material/Material.hpp"

namespace fox::ecs
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
            fox::uint32_t maxShadowCastingLights{ 8 }; //TODO: global config setting
            fox::bool_t   receiveShadows{ true };
        };

        std::shared_ptr<gfx::Mesh>     mesh{};
        std::shared_ptr<gfx::Material> material{};
        LightingOptions                lightingOptions{};
    };
}
