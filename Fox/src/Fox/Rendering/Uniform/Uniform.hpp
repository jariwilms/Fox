#pragma once

#include "stdafx.hpp"

namespace fox::gfx::unf
{
    //Graphics API's often enforce specific data layout requirements.
    //Padding may be automatically inserted when using certain data types to ensure proper alignment boundaries are maintained.
    //To prevent alignment-related issues, it is recommended to use the following types for uniform buffer data.
    //Reference: https://learn.microsoft.com/en-us/cpp/cpp/alignment-cpp-declarations?view=msvc-170

    using int32_t   = fox::int32_t;
    using uint32_t  = fox::uint32_t;
    using float32_t = fox::float32_t;
    using Vector2f  = fox::Vector2f;
    using Vector4f  = fox::Vector4f;
    using Matrix4f  = fox::Matrix4f;



    struct Context //Binding 0
    {
        unf::Vector2f  resolution{};
        unf::Vector2f  mousePosition{};
        unf::float32_t time{};
        unf::float32_t deltaTime{};
    };
    struct Camera //Binding 1
    {
        unf::Vector4f position{};
    };
    struct Matrices //Binding 2
    {
        unf::Matrix4f model     { 1.0f };
        unf::Matrix4f view      { 1.0f };
        unf::Matrix4f projection{ 1.0f };
    };
    struct Material //Binding 3
    {
        unf::Vector4f  color{};
        unf::float32_t roughness{};
        unf::float32_t metallic{};
    };
    struct Light //Binding 4
    {
        unf::Vector4f  position{};
        unf::Vector4f  color{};
        unf::float32_t radius{};
        unf::float32_t linearFalloff{};
        unf::float32_t quadraticFalloff{};

        unf::float32_t _padding{};
    };
    struct PreFilter //Binding 5
    {
        unf::uint32_t  resolution{};
        unf::float32_t value{};
    };
    struct LightShadow //Binding 6
    {
        unf::Vector4f  position{};
        unf::float32_t farPlane{};
    };
    using  SSAOSample = unf::Vector4f; //Binding 7 or smth idk
    struct ShadowProjection //Binding 13
    {
        unf::Matrix4f projection{ 1.0f };
    };
}
