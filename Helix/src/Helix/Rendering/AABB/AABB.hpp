#pragma once

#include "stdafx.hpp"

namespace hlx
{
    struct AABB
    {
    public:
        static bool intersects(const AABB& lhs, const AABB& rhs)
        {
            return
                lhs.min.x <= rhs.max.x &&
                lhs.max.x >= rhs.min.x &&
                lhs.min.y <= rhs.max.y &&
                lhs.max.y >= rhs.min.y &&
                lhs.min.z <= rhs.max.z &&
                lhs.max.z >= rhs.min.z;
        }

        Vector3f min{};
        Vector3f max{};
    };
    struct AABS
    {

    };
}
