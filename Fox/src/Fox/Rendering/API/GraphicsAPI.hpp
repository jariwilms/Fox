#pragma once

#include "stdafx.hpp"

#ifndef FOX_GRAPHICS_API
#define FOX_GRAPHICS_API OpenGL
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

    constexpr auto GRAPHICS_API = GraphicsAPI::OpenGL;
}
