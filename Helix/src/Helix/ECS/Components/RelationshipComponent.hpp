#pragma once

#include "stdafx.hpp"

#include "Component.hpp"

namespace hlx
{
    struct RelationshipComponent : public Component
    {
        std::optional<Id> parent{};
    };
}
