#pragma once

#include "stdafx.hpp"

namespace fox::gfx
{
    struct UMatrices //std140, binding 0
    {
        fox::Matrix4f model{ 1.0f };
        fox::Matrix4f view{ 1.0f };
        fox::Matrix4f projection{ 1.0f };
        fox::Matrix4f normal{ 1.0f };
    };
    struct UMaterial //std140, binding 1
    {
        fox::Vector4f  color{};
        fox::float32_t roughness{};
        fox::float32_t metallic{};
    };
    struct ULight //std140, binding 2
    {
        fox::Vector4f position{};
        fox::Vector4f color{};
    };
    struct UCamera //std140, binding 3
    {
        fox::Vector4f position{};
    };
}
