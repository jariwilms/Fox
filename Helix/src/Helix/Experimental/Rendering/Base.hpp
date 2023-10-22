#pragma once

#define HELIX_GRAPHICS_API GraphicsAPI::OpenGL

namespace hlx::gfx::api
{
    enum class GraphicsAPI
    {
        DirectX,
        Metal,
        OpenGL,
        Vulkan,
    };
    enum class Dimensions
    {
        _1D = 1u,
        _2D,
        _3D,
    };
    enum class AntiAliasing
    {
        None,
        MSAA,
    };

    constexpr auto GRAPHICS_API = HELIX_GRAPHICS_API;
}
