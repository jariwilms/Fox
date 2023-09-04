#pragma once

#include "stdafx.hpp"

namespace hlx
{
    struct Light
    {
    public:
        enum class Type
        {
            Point, 
            Directional, 
            Spot, 
            //Area, 
        };
        enum class Mode
        {
            Realtime, 
            //Mixed, 
            //Baked, 
        };

        Type type{};
        Mode mode{};
        Vector3f color{};

        float range{};
        float angle{};
        float intensity{};
    };
}
