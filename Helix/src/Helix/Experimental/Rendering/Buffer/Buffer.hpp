#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/Base.hpp"

namespace hlx::gfx::imp
{
    class Buffer
    {
    public:
        enum class Usage
        {
            Static,
            Dynamic,
        };
        enum class Type
        {
            Storage,

            Vertex,
            Index,

            Uniform,
        };
    };

    template<GraphicsAPI, Buffer::Type, typename>
    class GBuffer;
}
