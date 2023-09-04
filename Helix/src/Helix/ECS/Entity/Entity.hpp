#pragma once

#include "stdafx.hpp"

namespace hlx
{
    class Entity
    {
    public:
        Entity(Id id, std::weak_ptr<Entity> parent = {}, const std::vector<std::shared_ptr<Entity>>& children = {})
            : m_id{ id }, parent{ parent }, children{ children } {}
        virtual ~Entity() = default;

        Id id() const
        {
            return m_id;
        }

        bool operator==(const Entity& other) const = default;

        std::weak_ptr<Entity> parent{};
        std::vector<std::shared_ptr<Entity>> children{};

    protected:
        Id m_id{};
    };
}
