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

        Light() = default;
        Light(Type type, const fox::Vector3f& color)
            : type{ type }, color{ color } {}
        Light(Type type, const fox::Vector3f& color, fox::float32_t radius, fox::bool_t isShadowCasting = fox::False)
            : type{ type }, color{ color }, radius{ radius }, isShadowCasting{ isShadowCasting } {}
        Light(Type type, const fox::Vector3f& color, fox::float32_t radius, fox::float32_t linearFalloff, fox::float32_t quadraticFalloff, fox::bool_t isShadowCasting = fox::False)
            : type{ type }, color{ color }, radius{ radius }, linearFalloff{ linearFalloff }, quadraticFalloff{ quadraticFalloff }, isShadowCasting{ isShadowCasting } {}

        Type           type{};
        fox::Vector3f  color{ 1.0f };
        fox::float32_t radius{ 10.0f };
        fox::float32_t linearFalloff{ 0.7f };
        fox::float32_t quadraticFalloff{ 1.8f };
        fox::bool_t    isShadowCasting{};
    };
}
