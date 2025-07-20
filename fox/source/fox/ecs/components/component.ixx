export module fox.ecs.component;

import std;
import fox.ecs.entity;

export namespace fox::ecs
{
    template<typename T>
    class Component
    {
    public:
        explicit Component(const ecs::Entity& owner)
            : owner_{ owner }, value_{} {}
                 Component(const ecs::Entity& owner, const T& value)
            : owner_{ owner },  value_{ value } {}
        template<typename... Args>
                 Component(const ecs::Entity& owner, Args... args)
            : owner_{ owner }, value_{ std::forward<Args>(args)... } {}

        auto owner(this auto&& self) -> auto&&
        {
            return std::forward<decltype(self)>(self).owner_;
        }
        auto value(this auto&& self) -> auto&&
        {
            return std::forward<decltype(self)>(self).value_;
        }

    private:
        ecs::Entity owner_;
        T           value_;
    };
}
