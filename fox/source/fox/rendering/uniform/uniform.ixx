export module fox.rendering.uniform;

import std;

import fox.core.types;

export namespace fox::gfx::unf
{
    //Graphics API's often enforce specific data layout requirements.
    //Padding may be automatically inserted when using certain data types to ensure proper alignment boundaries are maintained.
    //To prevent alignment-related issues, it is recommended to use types that align fully on 4, 8, or 16 byte boundaries.
    //For more information: https://learn.microsoft.com/en-us/cpp/cpp/alignment-cpp-declarations?view=msvc-170

    //Binding 0
    struct context 
    {
        fox::vector2f  resolution;
        fox::vector2f  mousePosition;
        fox::float32_t time;
        fox::float32_t deltaTime;
    };

    //Binding 1
    struct camera 
    {
        fox::vector4f position;
    };

    //Binding 2
    struct matrices 
    {
        fox::matrix4f model      = fox::matrix<>::identity;
        fox::matrix4f view       = fox::matrix<>::identity;
        fox::matrix4f projection = fox::matrix<>::identity;
    };

    //Binding 3
    struct material 
    {
        fox::vector4f  color;
        fox::float32_t roughness;
        fox::float32_t metallic;
    };

    //Binding 4
    struct light 
    {
        fox::vector4f  position;
        fox::vector4f  color;
        fox::float32_t radius;
        fox::float32_t linearFalloff;
        fox::float32_t quadraticFalloff;

        fox::float32_t _;
    };

    //Binding 5
    struct pre_filter 
    {
        fox::uint32_t  resolution;
        fox::float32_t value;
    };

    //Binding 6
    struct light_shadow 
    {
        fox::vector4f  position;
        fox::float32_t farPlane;
    };

    //Binding 7 or smth idk
    using ssao_sample = fox::vector4f; 

    //Binding 13
    struct shadow_projection            
    {
        fox::matrix4f projection = fox::matrix<>::identity;
    };
}
