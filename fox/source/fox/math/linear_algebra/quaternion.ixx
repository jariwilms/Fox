export module fox.math.linear_algebra.quaternion;

import std;
import fox.core.types;
import vendor.glm;

export namespace fox::math
{
    constexpr auto conjugate     (const fox::quaternion4f& quaternion) -> fox::quaternion4f
    {
        return glm::conjugate(quaternion);
    }
              auto to_matrix     (const fox::quaternion4f& quaternion) -> fox::matrix4f
    {
        return glm::mat4_cast(quaternion);
    }
              auto angle_axis    (const fox::radians_t angle, const fox::vector3f axis) -> fox::quaternion4f
    {
        return glm::angleAxis(angle, axis);
    }
              auto compose_angles(const fox::vector3f& angle) -> fox::quaternion4f
    {
        auto x = math::angle_axis(angle.x, fox::vector3f{ 1.0f, 0.0f, 0.0f });
        auto y = math::angle_axis(angle.y, fox::vector3f{ 0.0f, 1.0f, 0.0f });
        auto z = math::angle_axis(angle.z, fox::vector3f{ 0.0f, 0.0f, 1.0f });

        return z * y * x;
    }
}
