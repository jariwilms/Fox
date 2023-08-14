#pragma once

#include "Component.hpp"

namespace hlx
{
    struct RelationshipComponent : public Component
    {
    public:
        Entity parent{};
        std::vector<Entity> children{};
    };
}
