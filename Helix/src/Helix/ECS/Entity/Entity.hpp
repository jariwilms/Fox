#pragma once

#include "stdafx.hpp"

namespace hlx
{
    class Entity
    {
    public:
        Entity(Id id)
            : m_id{ id } {}
        virtual ~Entity() = default;

        Id id() const
        {
            return m_id;
        }

        bool operator==(const Entity& other) const = default;

    protected:
        Id m_id{};
    };
}
