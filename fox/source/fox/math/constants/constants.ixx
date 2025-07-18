export module fox.math.constants;

import std;
import fox.core.types;

export namespace fox::math
{
    inline namespace constant
    {
        //Fundamental mathematical constants
        constexpr auto e           = fox::to_fundamental_type(std::numbers::e);
        constexpr auto pi          = fox::to_fundamental_type(std::numbers::pi);
        constexpr auto phi         = fox::to_fundamental_type(std::numbers::phi);
        constexpr auto tau         = fox::to_fundamental_type(pi * 2.0);

        //Logarithmic constants
        constexpr auto ln2         = fox::to_fundamental_type(std::numbers::ln2);
        constexpr auto ln10        = fox::to_fundamental_type(std::numbers::ln10);
        constexpr auto log2e       = fox::to_fundamental_type(std::numbers::log2e);
        constexpr auto log10e      = fox::to_fundamental_type(std::numbers::log10e);

        //Square root constants
        constexpr auto sqrt2       = fox::to_fundamental_type(std::numbers::sqrt2);
        constexpr auto sqrt3       = fox::to_fundamental_type(std::numbers::sqrt3);

        //Reciprocal constants
        constexpr auto inv_pi      = fox::to_fundamental_type(std::numbers::inv_pi);
        constexpr auto inv_sqrt_pi = fox::to_fundamental_type(std::numbers::inv_sqrtpi);
        constexpr auto inv_sqrt_3  = fox::to_fundamental_type(std::numbers::inv_sqrt3);
    }
}
