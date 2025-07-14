export module fox.math.constants;

import std;

import fox.core.types.fundamental;

export namespace fox::math
{
    inline namespace constant
    {
        //Fundamental mathematical constants
        inline constexpr auto e           = fox::to_fundamental_type(std::numbers::e);
        inline constexpr auto pi          = fox::to_fundamental_type(std::numbers::pi);
        inline constexpr auto phi         = fox::to_fundamental_type(std::numbers::phi);
        inline constexpr auto tau         = fox::to_fundamental_type(pi * 2.0);

        //Logarithmic constants
        inline constexpr auto ln2         = fox::to_fundamental_type(std::numbers::ln2);
        inline constexpr auto ln10        = fox::to_fundamental_type(std::numbers::ln10);
        inline constexpr auto log2e       = fox::to_fundamental_type(std::numbers::log2e);
        inline constexpr auto log10e      = fox::to_fundamental_type(std::numbers::log10e);

        //Square root constants
        inline constexpr auto sqrt2       = fox::to_fundamental_type(std::numbers::sqrt2);
        inline constexpr auto sqrt3       = fox::to_fundamental_type(std::numbers::sqrt3);

        //Reciprocal constants
        inline constexpr auto inv_pi      = fox::to_fundamental_type(std::numbers::inv_pi);
        inline constexpr auto inv_sqrt_pi = fox::to_fundamental_type(std::numbers::inv_sqrtpi);
        inline constexpr auto inv_sqrt_3  = fox::to_fundamental_type(std::numbers::inv_sqrt3);
    }
}
