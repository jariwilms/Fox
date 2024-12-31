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
    struct MapDimensionsToVector;

    template<> struct MapDimensionsToVector<Dimensions::_1D> { using type = fox::Vector1u; };
    template<> struct MapDimensionsToVector<Dimensions::_2D> { using type = fox::Vector2u; };
    template<> struct MapDimensionsToVector<Dimensions::_3D> { using type = fox::Vector3u; };
}
