#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Buffer/FrameBuffer.hpp"
#include "Helix/Rendering/Texture/AntiAliasing.hpp"

namespace hlx::gfx::imp
{
    inline namespace api
    {
        template<gfx::api::GraphicsAPI, gfx::api::AntiAliasing>
        class GFrameBuffer;
    }
}
