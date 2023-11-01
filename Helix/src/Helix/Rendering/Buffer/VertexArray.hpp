#pragma once

#include "Helix/Rendering/API/GraphicsAPI.hpp"

namespace hlx::gfx::api
{
    class VertexArray
    {
    protected:
        VertexArray() = default;
    };

    template<GraphicsAPI>
    class GVertexArray;
}
