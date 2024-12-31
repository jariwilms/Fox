#pragma once

#include "stdafx.hpp"

namespace fox::gfx
{
    enum class Dimensions
    {
        _1D = 1,
        _2D,
        _3D,
    };

    template<Dimensions>
    struct MapVectorType;

    template<> struct MapVectorType<Dimensions::_1D> { using type = Vector1u; };
    template<> struct MapVectorType<Dimensions::_2D> { using type = Vector2u; };
    template<> struct MapVectorType<Dimensions::_3D> { using type = Vector3u; };
}
