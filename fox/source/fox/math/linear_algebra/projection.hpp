#pragma once

#include <fox/core/types/math/math.hpp>

namespace fox::math
{
    static auto perspective (fox::float32_t ratio, fox::radians_t fov  , fox::float32_t near  , fox::float32_t far) -> fox::Matrix4f
    {
        return glm::perspective(fov, ratio, near, far);
    }
    static auto orthographic(fox::float32_t left , fox::float32_t right, fox::float32_t bottom, fox::float32_t top, fox::float32_t near, fox::float32_t far) -> fox::Matrix4f
    {
        return glm::ortho(left, right, bottom, top, near, far);
    }
}
