#pragma once

namespace fox::ecs
{
    class Entity
    {
    public:
        Entity(fox::id_t id)
            : m_id{ id } {}

        auto id() const
        {
            return m_id;
        }

    protected:
        id_t m_id{};
    };
}
