#pragma once

#include "stdafx.hpp"

#ifndef HLX_GRAPHICS_API
#define HLX_GRAPHICS_API OpenGL
#endif

namespace fox::gfx::api
{
    enum class GraphicsAPI
    {
        DirectX,
        Metal,
        OpenGL,
        Vulkan,
    };

    constexpr auto GRAPHICS_API = GraphicsAPI::HLX_GRAPHICS_API;
}