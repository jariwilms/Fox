#pragma once

#include <fox/core/types/fundamental/fundamental.hpp>
#include <fox/core/types/math/linear_algebra/vector.hpp>

namespace fox
{
    struct Light
    {
    public:
        enum class Type
        {
            Area, 
            Directional, 
            Point, 
            Spot, 
        };

        Light(Type type = Type::Point, const fox::Vector3f& color = vector::one, fox::float32_t radius = { 10.0f }, fox::bool_t isShadowCasting = { fox::False })
            : type{ type }, color{ color }, radius{ radius }, isShadowCasting{ isShadowCasting } {}

        Type           type;
        fox::Vector3f  color;
        fox::float32_t radius;
        fox::bool_t    isShadowCasting;
    };
}
