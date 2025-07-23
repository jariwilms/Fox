export module fox.ecs.component;

import std;
import fox.core.types;

export namespace fox::ecs
{
    template<typename T>
    class component
    {
    public:
        template<typename... Args>
        component(Args&&... args)
            : value_{ std::forward<Args>(args)... } {}

        auto value(this auto&& self) -> auto&&
        {
            return std::forward<decltype(self)>(self).value_;
        }

    private:
        T value_;
    };
}
