#pragma once

namespace hlx
{
    class Entity
    {
    public:
        explicit Entity(Id id)
            : m_id{ id } {}
        virtual ~Entity() = default;

        Id id() const
        {
            return m_id;
        }

        const std::shared_ptr<Entity> parent() const
        {
            return m_parent;
        }
        const std::vector<std::shared_ptr<Entity>>& children() const
        {
            return m_children;
        }

        bool operator==(const Entity& other) const
        {
            return m_id == other.m_id;
        }

    private:
        Id m_id{};

        std::shared_ptr<Entity> m_parent{};
        std::vector<std::shared_ptr<Entity>> m_children{};
    };
}
