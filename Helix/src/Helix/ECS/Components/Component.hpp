#pragma once

#include "stdafx.hpp"

#include "Helix/ECS/Entity/Entity.hpp"

namespace hlx
{
    struct Component
    {
    public:
        virtual ~Component() = default;

        Entity entity{};

    protected:
        Component(Entity entity)
            : entity{ entity } {}
    };
}
