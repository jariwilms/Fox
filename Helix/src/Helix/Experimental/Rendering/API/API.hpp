#pragma once

#include "stdafx.hpp"

#ifndef HLX_GRAPHICS_API
#define HLX_GRAPHICS_API OpenGL
#endif

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

    template<Dimensions D>
    struct DimensionToVector {};
    template<> struct DimensionToVector<Dimensions::_1D> { using type = Vector1u; };
    template<> struct DimensionToVector<Dimensions::_2D> { using type = Vector2u; };
    template<> struct DimensionToVector<Dimensions::_3D> { using type = Vector3u; };

    constexpr auto GRAPHICS_API = GraphicsAPI::HLX_GRAPHICS_API;
}