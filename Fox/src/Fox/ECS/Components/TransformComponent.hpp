#pragma once

#include "Fox/Core/Library/Transform/Transform.hpp"
#include "Fox/ECS/Components/Component.hpp"

namespace fox::ecs
{
    struct TransformComponent : public Component
    {
    public:
        TransformComponent(Entity& parent)
            : Component{ parent } {}
        TransformComponent(Entity& parent, const Transform& transform)
            : Component{ parent }, m_transform{ transform } {}
        TransformComponent(Entity& parent, const Matrix4f& prs)
            : Component{ parent }, m_transform{ prs } {}
        virtual ~TransformComponent() = default;

        Transform& transform()
        {
            return m_transform;
        }

    protected:
        Transform m_transform;
    };
}
