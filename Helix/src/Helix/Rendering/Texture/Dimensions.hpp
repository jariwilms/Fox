#pragma once

#include "stdafx.hpp"

namespace hlx::gfx::api
{
    enum class Dimensions
    {
        _1D = 1,
        _2D,
        _3D,
    };

    template<Dimensions D>
    struct DimensionsToVector;
    template<> struct DimensionsToVector<Dimensions::_1D> { using type = Vector1u; };
    template<> struct DimensionsToVector<Dimensions::_2D> { using type = Vector2u; };
    template<> struct DimensionsToVector<Dimensions::_3D> { using type = Vector3u; };
}
