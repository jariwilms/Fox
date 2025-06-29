#pragma once

#include <type_traits>

#include <fox/core/types/fundamental/fundamental.hpp>

namespace fox::gfx::api
{
	template<typename T>
    concept valid_layout_component_c = requires
    {
        std::is_same_v<T, fox::int8_t>    ||
        std::is_same_v<T, fox::uint8_t>   ||
        std::is_same_v<T, fox::int16_t>   ||
        std::is_same_v<T, fox::uint16_t>  ||
        std::is_same_v<T, fox::int32_t>   ||
        std::is_same_v<T, fox::uint32_t>  ||
        std::is_same_v<T, fox::float32_t>  ;
    };
}
