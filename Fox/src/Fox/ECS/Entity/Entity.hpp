#pragma once

#include "Fox/ECS/Types.hpp"

namespace fox::ecs
{
    class Entity
    {
    public:
        Entity(ecs::id_t id)
            : m_id{ id } {}
        virtual ~Entity() = default;

        id_t id() const
        {
            return m_id;
        }

    protected:
        id_t m_id{};
    };
}
