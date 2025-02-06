#pragma once

#include "stdafx.hpp"

#include "Fox/Core/Library/Template/Concepts.hpp"

namespace fox::gfx::api
{
    template<typename T, fox::uint32_t COUNT>
    concept LayoutRequirements = requires
    {
        std::is_fundamental_v<T>;
        GreaterThanZero<decltype(COUNT), COUNT>;
    };

    template<typename T, fox::uint32_t COUNT, fox::bool_t NORM = false> requires LayoutRequirements<T, COUNT>
    class Layout
    {
    public:
        using type = T;

        static inline const fox::uint32_t count        = COUNT;
        static inline const fox::bool_t   isNormalized = NORM;
    };
}
