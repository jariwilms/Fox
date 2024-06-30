#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/GraphicsAPI.hpp"
#include "Fox/Rendering/Renderer/Renderer.hpp"

namespace fox::gfx::imp
{
    inline namespace api
    {
        template<gfx::api::GraphicsAPI>
        class GRenderer;
    }
}
