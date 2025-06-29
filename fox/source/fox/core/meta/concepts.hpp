#pragma once

#include <stdafx.hpp>

namespace fox
{
    template<typename T, T N> concept non_zero_c = std::is_arithmetic_v<T> && (N != 0);
    template<typename T, T N> concept lt_zero_c  = std::is_arithmetic_v<T> && (N  < 0);
    template<typename T, T N> concept gt_zero_c  = std::is_arithmetic_v<T> && (N  > 0);
}
