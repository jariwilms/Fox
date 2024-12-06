#pragma once

#include "stdafx.hpp"

namespace fox
{
    template<typename T, T N> concept NonZero         = std::is_arithmetic_v<T> && N != T{ 0 };
    template<typename T, T N> concept LessThanZero    = std::is_arithmetic_v<T> && N  < T{ 0 };
    template<typename T, T N> concept GreaterThanZero = std::is_arithmetic_v<T> && N  > T{ 0 };
}