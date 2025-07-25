export module fox.core.meta.concepts;

import std;
import fox.core.types;

export namespace fox::meta
{
    template<typename T, typename... Ts>
    constexpr auto all_same_type_v = fox::bool_t{ std::conjunction_v<std::is_same<T, Ts>...> };
    
    template<auto value, auto min, auto max>
    constexpr auto within_open_interval_v   = value >  min && value <  max;
    template<auto value, auto min, auto max>
    constexpr auto within_closed_interval_v = value >= min && value <= max;
}
