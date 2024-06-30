#pragma once

#include "stdafx.hpp"

namespace hlx
{
    template<typename T, T N> concept NonZero = std::is_arithmetic_v<T> && N != T{};
}