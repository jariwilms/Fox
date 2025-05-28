#pragma once

#include "stdafx.hpp"

namespace fox::gfx::unf
{
    //Some graphics API's specify certain rules for data layouts.
    //It is recommended to exclusively use the following types for uniform data 
    //in order to prevent alignment issues: 

    using int32_t   = fox::int32_t;
    using uint32_t  = fox::uint32_t;
    using float32_t = fox::float32_t;
    using Vector2f  = fox::Vector2f;
    using Vector4f  = fox::Vector4f;
    using Matrix4f  = fox::Matrix4f;



    //Binding 0
    struct Context
    {
        unf::Vector2f  resolution{};
        unf::Vector2f  mousePosition{};
        unf::float32_t time{};
        unf::float32_t deltaTime{};
    };

    //Binding 1
    struct Camera
    {
        unf::Vector4f position{};
    };
    
    //Binding 2
    struct Matrices
    {
        unf::Matrix4f model     { 1.0f };
        unf::Matrix4f view      { 1.0f };
        unf::Matrix4f projection{ 1.0f };
    };
    
    //Binding 3
    struct Material
    {
        unf::Vector4f  color{};
        unf::float32_t roughness{};
        unf::float32_t metallic{};
    };
    
    //Binding 4
    struct Light
    {
        unf::Vector4f  position{};
        unf::Vector4f  color{};
        unf::float32_t radius{};
        unf::float32_t linearFalloff{};
        unf::float32_t quadraticFalloff{};

        unf::float32_t _padding{};
    };
    
    //Binding 5
    struct PreFilter
    {
        unf::uint32_t  resolution{};
        unf::float32_t value{};
    };
    
    //Binding 6
    struct LightShadow
    {
        unf::Vector4f  position{};
        unf::float32_t farPlane{};
    };
    
    //Binding 13
    struct ShadowProjection
    {
        unf::Matrix4f projection{ 1.0f };
    };

    //Binding 7...? maybe.
    using SSAOSample = unf::Vector4f;
}
