#pragma once

#include "stdafx.hpp"

#include "Component.hpp"

namespace hlx
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
