#pragma once

#include "Helix/ECS/Registry.hpp"

namespace hlx
{
    class Scene
    {
    public:
        Scene() = default;

        Entity create_entity();
        void destroy_entity(Entity entity);

        std::vector<Entity> entities{};
    };
}
