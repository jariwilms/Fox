#pragma once

#include "Component.hpp"

#include "Fox/Core/Library/Transform/Transform.hpp"

namespace fox
{
    struct TransformComponent : public Transform, public Component
    {
    public:
        TransformComponent(Entity& parent)
            : Component{ parent } {}
        TransformComponent(Entity& parent, const Transform& transform)
            : Component{ parent }, Transform{ transform } {}
        TransformComponent(Entity& parent, const Matrix4f& prs)
            : Component{ parent }, Transform{ prs } {}
        virtual ~TransformComponent() = default;
    };
}
