#pragma once

#include <fox/core/types/math/linear_algebra/quaternion.hpp>
#include <fox/core/types/math/linear_algebra/vector.hpp>

namespace fox::math
{
    static constexpr auto conjugate(const fox::Quaternion& quaternion) -> fox::Quaternion
    {
        return glm::conjugate(quaternion);
    }
    static           auto to_matrix(const fox::Quaternion& quaternion) -> fox::Matrix4f
    {
        return glm::mat4_cast(quaternion);
    }
}
