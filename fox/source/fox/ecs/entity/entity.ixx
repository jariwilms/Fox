export module fox.ecs.entity;

import fox.core.types.ecs;

export namespace fox::ecs
{
    class Entity
    {
    public:
        auto id() const -> fox::id_t
        {
            return id_;
        }

    protected:
        explicit Entity(fox::id_t id)
            : id_{ id } {}

        fox::id_t id_{};
    };
}
