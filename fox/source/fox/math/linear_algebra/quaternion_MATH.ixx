export module fox.math.linear_algebra.quaternion;

import fox.core.types;

import vendor.glm;

export namespace fox::math
{
    constexpr auto conjugate(const fox::Quaternion& quaternion) -> fox::Quaternion
    {
        return glm::conjugate(quaternion);
    }
              auto to_matrix(const fox::Quaternion& quaternion) -> fox::Matrix4f
    {
        return glm::mat4_cast(quaternion);
    }
}
