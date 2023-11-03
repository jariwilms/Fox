#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Renderer/Renderer.hpp"

namespace hlx::gfx::imp::api
{
    inline namespace api
    {
        template<gfx::api::GraphicsAPI>
        class GRenderer;
    }
}
