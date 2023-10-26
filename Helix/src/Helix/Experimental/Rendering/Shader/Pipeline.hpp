#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/API/API.hpp"

namespace hlx::gfx::api
{
    class Pipeline
    {
    protected:
        Pipeline() = default;
    };

    template<GraphicsAPI G>
    class GPipeline;
}
