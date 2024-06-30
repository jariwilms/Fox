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
        Vector3f color{};
        float radius{};
    };
    //struct DirectionalLight : Light
    //{
    //    float angle{};
    //};
}
