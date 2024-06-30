#pragma once

#include "stdafx.hpp"

#include "Component.hpp"

namespace fox
{
    struct RelationshipComponent : public Component
    {
    public:
        RelationshipComponent(Entity& parent)
            : Component{ parent } {}

        std::optional<Id> parent{};
        std::vector<Id> children{};
    };
}
