#pragma once

import fox.core.types.fundamental;
#include <fox/core/types/math/linear_algebra/matrix.hpp>
#include <fox/core/types/math/math.hpp>

namespace fox::math
{
    inline auto perspective (fox::float32_t ratio, fox::radians_t fov  , fox::float32_t near  , fox::float32_t far) -> fox::Matrix4f
    {
        return glm::perspective(fov, ratio, near, far);
    }
    inline auto orthographic(fox::float32_t left , fox::float32_t right, fox::float32_t bottom, fox::float32_t top, fox::float32_t near, fox::float32_t far) -> fox::Matrix4f
    {
        return glm::ortho(left, right, bottom, top, near, far);
    }
}
