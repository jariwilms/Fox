#pragma once

#include "stdafx.hpp"

namespace fox::gfx::unf
{
    //Binding 0
    struct Context
    {
        fox::Vector2f  resolution{};
        fox::Vector2f  mousePosition{};
        fox::float32_t time{};
        fox::float32_t deltaTime{};
    };

    //Binding 1
    struct Camera
    {
        fox::Vector4f position{};
    };
    //Binding 2
    struct Matrices
    {
        fox::Matrix4f model{ 1.0f };
        fox::Matrix4f view{ 1.0f };
        fox::Matrix4f projection{ 1.0f };
    };
    //Binding 3
    struct Material
    {
        fox::Vector4f  color{};
        fox::float32_t roughness{};
        fox::float32_t metallic{};
    };

    //Binding 4
    struct Light
    {
        fox::Vector4f  position{};
        fox::Vector4f  color{};
        fox::float32_t radius{};
        fox::float32_t linearFalloff{};
        fox::float32_t quadraticFalloff{};

        fox::float32_t _padding{};
    };
    //Binding 6
    struct LightShadow
    {
        fox::Vector4f  position{};
        fox::float32_t farPlane{};
    };
    //Binding 13
    struct ShadowProjection
    {
        fox::Matrix4f projection{ 1.0f };
    };
}
