#pragma once

#include "stdafx.hpp"

#include "Component.hpp"

namespace hlx
{
    struct LightComponent
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
