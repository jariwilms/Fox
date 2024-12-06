#pragma once

#include "stdafx.hpp"

#include "Fox/ECS/Components/Component.hpp"

namespace fox::ecs
{
    struct RelationshipComponent : public Component
    {
    public:
        RelationshipComponent(Entity& parent)
            : Component{ parent } {}

        std::optional<fox::id_t> parent{};
        std::vector<fox::id_t>   children{};
    };
}
