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

        Type           type{ Type::Point };
        fox::Vector3f  color{ 1.0f };
        fox::float32_t radius{ 10.0f };
        fox::float32_t linearFalloff{ 0.7f };
        fox::float32_t quadraticFalloff{ 1.8f };
        fox::bool_t    isShadowCasting{ false };
    };
}
