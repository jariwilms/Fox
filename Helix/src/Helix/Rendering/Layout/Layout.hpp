#pragma once

#include "stdafx.hpp"

#include "Helix/Core/Library/Template/Concepts.hpp"

namespace hlx::gfx::api
{
    template<typename T, u32 COUNT>
    concept LayoutRequirements = requires
    {
        std::is_fundamental_v<T>;
        NonZero<decltype(COUNT), COUNT>; //TODO greater than zero concept instead of non zero
    };

    template<typename T, u32 COUNT, bool NORM = false> requires LayoutRequirements<T, COUNT>
    class Layout
    {
    public:
        using type = T;

        static inline const u32  count        = COUNT;
        static inline const bool isNormalized = NORM;
    };
}
