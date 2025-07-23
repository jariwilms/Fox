export module fox.math.linear_algebra.quaternion;

import std;
import fox.core.types;
import vendor.glm;

export namespace fox::math
{
    constexpr auto conjugate(const fox::quaternion4f& quaternion) -> fox::quaternion4f
    {
        return glm::conjugate(quaternion);
    }
              auto to_matrix(const fox::quaternion4f& quaternion) -> fox::matrix4f
    {
        return glm::mat4_cast(quaternion);
    }
}
