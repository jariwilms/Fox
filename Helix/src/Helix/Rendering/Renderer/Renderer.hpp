#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/GraphicsAPI.hpp"

namespace hlx::gfx::api
{
    class Renderer
    {
    protected:
        Renderer() = default;
    };

    template<GraphicsAPI>
    class GRenderer;
}
