#pragma once

#include "stdafx.hpp"

namespace fox::ecs
{
    class Entity
    {
    public:
        Entity(fox::id_t id)
            : m_id{ id } {}
        virtual ~Entity() = default;

        fox::id_t id() const
        {
            return m_id;
        }

    protected:
        fox::id_t m_id{};
    };
}
