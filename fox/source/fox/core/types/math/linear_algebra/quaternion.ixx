export module fox.core.types.math.linear_algebra.quaternion;

import fox.core.types.fundamental;
import vendor.glm;

export namespace fox
{
    using Quaternion = glm::quat;

    namespace quaternion
    {
        const auto identity = fox::Quaternion{ 1.0f, 0.0f, 0.0f, 0.0f };
    }
}
