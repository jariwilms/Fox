#pragma once

#include <fox/core/meta/concepts.hpp>
#include <fox/core/types/fundamental/fundamental.hpp>

namespace fox::gfx::api
{
    template<typename T, fox::uint32_t COUNT>
    concept layout_requirements_c = requires
    {
        std::is_fundamental_v<T>;
        fox::gt_zero_c<decltype(COUNT), COUNT>;
    };

    template<typename T, fox::uint32_t COUNT, fox::bool_t NORM = false> requires layout_requirements_c<T, COUNT>
    class Layout
    {
    public:
        using type = T;

        static inline const fox::uint32_t count        = COUNT;
        static inline const fox::bool_t   isNormalized = NORM;
    };
}
