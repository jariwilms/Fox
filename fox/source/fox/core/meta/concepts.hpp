#pragma once

#include <type_traits>
#include <utility>

namespace fox
{
    template<typename T, T N> concept NonZero         = std::is_arithmetic_v<T> && std::cmp_not_equal(N, T{ 0u });
    template<typename T, T N> concept LessThanZero    = std::is_arithmetic_v<T> && std::cmp_less     (N, T{ 0u });
    template<typename T, T N> concept GreaterThanZero = std::is_arithmetic_v<T> && std::cmp_less     (N, T{ 0u });
}