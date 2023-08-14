#pragma once

#include "Component.hpp"

#include "Helix/Core/Library/Transform/Transform.hpp"

namespace hlx
{
    struct TransformComponent : public Component
    {
    public:
        TransformComponent() = default;
        virtual ~TransformComponent() = default;

        //const Transform& local_transform() const
        //{
        //    return m_transform;
        //}
        //const Transform& global_transform() const
        //{
        //    if (!m_parent.expired())
        //    {
        //        const auto parent = m_parent.lock();
        //        return parent->global_transform() * local_transform();
        //    }
        //}

        operator Transform&()
        {
            return m_transform;
        }
        operator const Transform&() const
        {
            return m_transform;
        }

    protected:
        Transform m_transform{};
        //std::weak_ptr<TransformComponent> m_parent{};
    };
}
