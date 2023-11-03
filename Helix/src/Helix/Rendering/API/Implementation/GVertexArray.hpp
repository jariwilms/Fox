#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Buffer/VertexArray.hpp"

namespace hlx::gfx::imp
{
    inline namespace api
    {
        template<gfx::api::GraphicsAPI>
        class GVertexArray;
    }
}
