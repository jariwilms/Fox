#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/GraphicsAPI.hpp"
#include "Fox/Rendering/Texture/Texture.hpp"

namespace fox::gfx::imp
{
    inline namespace api
    {
        template<gfx::api::GraphicsAPI, gfx::api::AntiAliasing>
        class GRenderBuffer;
    }
}
