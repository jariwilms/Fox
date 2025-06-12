#pragma once

#include <fox/core/types/ecs/ecs.hpp>

namespace fox::ecs
{
    class Entity
    {
    public:
        auto id() const -> fox::id_t
        {
            return m_id;
        }

    protected:
        Entity(fox::id_t id)
            : m_id{ id } {}

        fox::id_t m_id{};
    };
}
