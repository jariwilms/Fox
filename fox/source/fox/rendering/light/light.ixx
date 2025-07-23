export module fox.rendering.light;

import fox.core.types;

export namespace fox
{
    struct light
    {
        enum class type_e
        {
            area, 
            directional, 
            point, 
            spot, 
        };

        light(type_e type = type_e::point, const fox::vector3f& color = fox::vector<>::one, fox::float32_t radius = { 10.0f }, fox::bool_t isShadowCasting = { fox::false_ })
            : type{ type }, color{ color }, radius{ radius }, isShadowCasting{ isShadowCasting } {}

        type_e         type;
        fox::vector3f  color;
        fox::float32_t radius;
        fox::bool_t    isShadowCasting;
    };
}
