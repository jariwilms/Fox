#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Core/Library/Template/Concepts.hpp"

namespace hlx::gfx
{
    template<typename T, u32 COUNT>
    concept LayoutRequirements = requires
    {
        std::is_fundamental_v<T>;
        NonZero<decltype(COUNT), COUNT>;
    };

    template<typename T, u32 COUNT, bool NORM = false> requires LayoutRequirements<T, COUNT>
    class Layout
    {
    public:
        using type = T;

        static inline const u32  count        = COUNT;
        static inline const bool isNormalized = NORM;
    };

    namespace api
    {
        template<GraphicsAPI G>
        struct GAttribute;

        template<GraphicsAPI G, typename... T>
        class GVertexLayout;
    }
}
