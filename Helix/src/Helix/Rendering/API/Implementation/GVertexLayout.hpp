#pragma once

#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Layout/Layout.hpp"

namespace hlx::gfx::imp
{
    inline namespace api
    {
        template<gfx::api::GraphicsAPI G>
        struct GAttribute;

        template<gfx::api::GraphicsAPI G, typename... T>
        class GVertexLayout;
    }
}
