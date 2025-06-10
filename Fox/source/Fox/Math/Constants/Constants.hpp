#pragma once

#include "stdafx.hpp"

namespace fox::math::constant
{
    //Fundamental mathematical constants
    inline constexpr auto e           = std::numbers::e;
    inline constexpr auto pi          = std::numbers::pi;
    inline constexpr auto phi         = std::numbers::phi;
    inline constexpr auto tau         = pi * 2.0;

    //Logarithmic constants
    inline constexpr auto ln2         = std::numbers::ln2;
    inline constexpr auto ln10        = std::numbers::ln10;
    inline constexpr auto log2e       = std::numbers::log2e;
    inline constexpr auto log10e      = std::numbers::log10e;

    //Square root constants
    inline constexpr auto sqrt2       = std::numbers::sqrt2;
    inline constexpr auto sqrt3       = std::numbers::sqrt3;

    //Reciprocal constants
    inline constexpr auto inv_pi      = std::numbers::inv_pi;
    inline constexpr auto inv_sqrt_pi = std::numbers::inv_sqrtpi;
    inline constexpr auto inv_sqrt_3  = std::numbers::inv_sqrt3;
}
