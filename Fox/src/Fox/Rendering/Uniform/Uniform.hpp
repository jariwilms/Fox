#pragma once

#include "stdafx.hpp"

namespace fox::gfx
{
    struct UInput    //Binding 0
    {
        fox::Vector2f  resolution{};
        fox::float32_t time{};
        fox::float32_t deltaTime{};
        fox::Vector2f  mousePosition{};
    };
    struct UMatrices //Binding 1
    {
        fox::Matrix4f model{ 1.0f };
        fox::Matrix4f view{ 1.0f };
        fox::Matrix4f projection{ 1.0f };
        fox::Matrix4f normal{ 1.0f };
    };
    struct UCamera   //Binding 2
    {
        fox::Vector4f position{};
    };
    struct UMaterial //Binding 3
    {
        fox::Vector4f  color{ 1.0f, 1.0f, 1.0f, 1.0f };
        fox::float32_t roughness{};
        fox::float32_t metallic{};
    };
    struct ULight    //Binding 4
    {
        fox::Vector4f  position{};
        fox::Vector4f  color{ 1.0f, 1.0f, 1.0f, 1.0f };
        fox::float32_t radius{ 1.0f };
        fox::float32_t linearFalloff{ 1.0f };
        fox::float32_t quadraticFalloff{ 1.0f };
        fox::float32_t _padding{};
    };
}
