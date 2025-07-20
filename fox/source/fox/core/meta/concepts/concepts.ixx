export module fox.core.meta.concepts;

import std;
import fox.core.types;

export namespace fox::meta
{
    inline namespace concepts
    {
        template<typename T, typename... Ts>
        constexpr auto all_same_type = fox::bool_t{ std::conjunction_v<std::is_same<T, Ts>...> };

        template<auto value, auto min, auto max>
        concept within_open_interval = requires
        {
            value > min and value < max;
        };
        template<auto value, auto min, auto max>
        concept within_closed_interval = requires
        {
            value >= min and value <= max;
        };
    }
}
