export module fox.rendering.geometry.data;

import std;

import fox.core.types;

export namespace fox::gfx::geometry::data
{
    namespace plane
    {
        constexpr std::array<fox::float32_t, 12u> positions
        {
             1.0f,  1.0f,  0.0f,
            -1.0f,  1.0f,  0.0f,
            -1.0f, -1.0f,  0.0f,
             1.0f, -1.0f,  0.0f,
        };
        constexpr std::array<fox::float32_t, 12u> normals
        {
             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,
        };
        constexpr std::array<fox::float32_t, 12u> tangents
        {
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
        };
        constexpr std::array<fox::float32_t,  8u> coordinates
        {
             1.0f,  1.0f,
             0.0f,  1.0f,
             0.0f,  0.0f,
             1.0f,  0.0f,
        };
        constexpr std::array<fox::uint32_t ,  6u> indices
        {
               0u,    1u,    2u,
               0u,    2u,    3u,
        };
    }
    namespace cube
    {
        constexpr std::array<fox::float32_t, 72u> positions
        {
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,

             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,

             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,

             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
        };
        constexpr std::array<fox::float32_t, 72u> normals
        {
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,

            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,

             0.0f,  1.0f,  0.0f,
             0.0f,  1.0f,  0.0f,
             0.0f,  1.0f,  0.0f,
             0.0f,  1.0f,  0.0f,

             0.0f, -1.0f,  0.0f,
             0.0f, -1.0f,  0.0f,
             0.0f, -1.0f,  0.0f,
             0.0f, -1.0f,  0.0f,

             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,

             0.0f,  0.0f, -1.0f,
             0.0f,  0.0f, -1.0f,
             0.0f,  0.0f, -1.0f,
             0.0f,  0.0f, -1.0f,
        };
        constexpr std::array<fox::float32_t, 72u> tangents
        {
             0.0f,  0.0f, -1.0f,
             0.0f,  0.0f, -1.0f,
             0.0f,  0.0f, -1.0f,
             0.0f,  0.0f, -1.0f,

             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,

             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,

             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,

             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,

            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
        };
        constexpr std::array<fox::float32_t, 48u> coordinates
        {
             1.0f,  1.0f,
             0.0f,  1.0f,
             0.0f,  0.0f,
             1.0f,  0.0f,

             1.0f,  1.0f,
             0.0f,  1.0f,
             0.0f,  0.0f,
             1.0f,  0.0f,

             1.0f,  1.0f,
             0.0f,  1.0f,
             0.0f,  0.0f,
             1.0f,  0.0f,

             1.0f,  1.0f,
             0.0f,  1.0f,
             0.0f,  0.0f,
             1.0f,  0.0f,

             1.0f,  1.0f,
             0.0f,  1.0f,
             0.0f,  0.0f,
             1.0f,  0.0f,

             1.0f,  1.0f,
             0.0f,  1.0f,
             0.0f,  0.0f,
             1.0f,  0.0f,
        };
        constexpr std::array<fox::uint32_t , 36u> indices
        {
               0u,    1u,    2u,
               0u,    2u,    3u,

               4u,    5u,    6u,
               4u,    6u,    7u,

               8u,    9u,   10u,
               8u,   10u,   11u,

              12u,   13u,   14u,
              12u,   14u,   15u,

              16u,   17u,   18u,
              16u,   18u,   19u,

              20u,   21u,   22u,
              20u,   22u,   23u,
        };
    }
}
