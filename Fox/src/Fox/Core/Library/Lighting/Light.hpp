#pragma once

#include "stdafx.hpp"

namespace fox
{
    struct Light
    {
    public:
        enum class Type
        {
            Point, 
            Directional, 
            Spot, 
            Area, 
        };
        enum class Mode
        {
            Realtime, 
            Mixed, 
            Baked, 
        };

        Type           type{};
        fox::Vector3f  color{};
        fox::float32_t radius{};
    };
}
