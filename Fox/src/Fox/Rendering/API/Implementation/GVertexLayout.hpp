#pragma once

#include "Fox/Rendering/API/GraphicsAPI.hpp"
#include "Fox/Rendering/Layout/Layout.hpp"

namespace fox::gfx::imp
{
    inline namespace api
    {
        template<gfx::api::GraphicsAPI G>
        struct GAttribute;

        template<gfx::api::GraphicsAPI G, typename... T>
        class GVertexLayout;
    }
}
