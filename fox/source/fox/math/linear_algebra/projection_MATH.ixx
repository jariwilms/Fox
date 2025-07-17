export module fox.math.linear_algebra.projection;

import fox.core.types;

import vendor.glm;

export namespace fox::math
{
    auto perspective (fox::float32_t ratio, fox::radians_t fov  , fox::float32_t near  , fox::float32_t far) -> fox::Matrix4f
    {
        return glm::perspective(fov, ratio, near, far);
    }
    auto orthographic(fox::float32_t left , fox::float32_t right, fox::float32_t bottom, fox::float32_t top, fox::float32_t near, fox::float32_t far) -> fox::Matrix4f
    {
        return glm::ortho(left, right, bottom, top, near, far);
    }
}
