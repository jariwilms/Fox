#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/GraphicsAPI.hpp"
#include "Fox/Rendering/Buffer/FrameBuffer.hpp"
#include "Fox/Rendering/Texture/AntiAliasing.hpp"

namespace fox::gfx::imp
{
    inline namespace api
    {
        template<gfx::api::GraphicsAPI, gfx::api::AntiAliasing>
        class GFrameBuffer;
    }
}
