#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/API/API.hpp"
#include "Helix/Core/Library/Template/Concept.hpp"

namespace hlx::gfx::api
{
    template<typename T, u32 C, bool N = false> requires std::is_fundamental_v<T> && NonZero<u32, C>
    class Layout
    {
    public:
        using type = T;

        static inline const u32  count        = C;
        static inline const bool isNormalized = N;
    };

    template<GraphicsAPI G>
    struct Attribute;

    template<GraphicsAPI G, typename... T>
    class VertexLayout;
}
