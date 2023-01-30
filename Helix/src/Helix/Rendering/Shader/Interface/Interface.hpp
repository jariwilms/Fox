#pragma once

#include "stdafx.hpp"

namespace hlx
{
    struct UMatrices //std140, binding 0
    {
        Matrix4f model{ 1.0f };
        Matrix4f view{ 1.0f };
        Matrix4f projection{ 1.0f };
    };
    struct UMaterial //std140, binding 1
    {
        Vector4f color{ 1.0f };
        float metallic{};
        float roughness{};
    };
    struct ULight //std140, binding 2
    {
        Vector4f position{};
        Vector4f color{ 1.0f };
        float linear{};
        float quadratic{};
        float radius{ 1.0f };
    };
    struct UCamera //std140, binding 3
    {
        Vector4f position{};
    };
}