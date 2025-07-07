#pragma once

#include <fox/core/types/math/linear_algebra/matrix.hpp>
#include <fox/core/types/math/linear_algebra/quaternion.hpp>

namespace fox::math
{
    inline constexpr auto conjugate(const fox::Quaternion& quaternion) -> fox::Quaternion
    {
        return glm::conjugate(quaternion);
    }
    inline           auto to_matrix(const fox::Quaternion& quaternion) -> fox::Matrix4f
    {
        return glm::mat4_cast(quaternion);
    }
}
