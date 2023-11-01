#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/GraphicsAPI.hpp"

namespace hlx::gfx::api
{
    class Pipeline
    {
    protected:
        Pipeline() = default;
    };

    template<GraphicsAPI>
    class GPipeline;
}
