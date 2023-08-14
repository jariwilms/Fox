#pragma once

namespace hlx
{
    //TODO: subclass to actor? => scene creates actors instead of entity => can just be passed to registry by polymorphism
    class Entity
    {
    public:
        explicit Entity(Id id = 0, std::shared_ptr<Entity> parent = {})
            : m_id{ id } {}
        virtual ~Entity() = default;

        Id id() const
        {
            return m_id;
        }

        bool operator==(const Entity& other) const = default;

    private:
        Id m_id{};
    };
}
