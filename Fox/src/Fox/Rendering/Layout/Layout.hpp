#pragma once

#include "stdafx.hpp"

#include "Fox/Core/Library/Template/Concepts.hpp"

namespace fox::gfx::api
{
    template<typename T, std::uint32_t COUNT>
    concept LayoutRequirements = requires
    {
        std::is_fundamental_v<T>;
        NonZero<decltype(COUNT), COUNT>; //TODO greater than zero concept instead of non zero
    };

    template<typename T, std::uint32_t COUNT, bool NORM = false> requires LayoutRequirements<T, COUNT>
    class Layout
    {
    public:
        using type = T;

        static inline const std::uint32_t  count        = COUNT;
        static inline const bool isNormalized = NORM;
    };
}
