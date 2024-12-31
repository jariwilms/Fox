#pragma once

#include "stdafx.hpp"

namespace fox::gfx
{
	template<typename T>
    concept IsValidLayoutComponent = requires
    {
        std::is_same_v<T, fox::int8_t>   ||
        std::is_same_v<T, fox::uint8_t>  ||
        std::is_same_v<T, fox::int16_t>  ||
        std::is_same_v<T, fox::uint16_t> ||
        std::is_same_v<T, fox::int32_t>  ||
        std::is_same_v<T, fox::uint32_t> ||
        std::is_same_v<T, fox::float32_t>;
    };
}
