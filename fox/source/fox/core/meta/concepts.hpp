#pragma once

#include <fox/core/utility/utility.hpp>

import std;

namespace fox::meta
{
    inline namespace concepts
    {
        template<auto value, auto min, auto max>
        concept in_open_interval = requires
        {
            fox::compare<std::greater>(value, min) and fox::compare<std::less>(value, max);
        };
        template<auto value, auto min, auto max>
        concept in_closed_interval = requires
        {
            fox::compare<std::greater_equal>(value, min) and fox::compare<std::less_equal>(value, max);
        };
    }
}
