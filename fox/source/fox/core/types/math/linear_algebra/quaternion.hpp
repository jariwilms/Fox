#pragma once

import vendor.glm;

namespace fox
{
    using Quaternion = glm::quat;

    namespace quaternion
    {
        const auto identity = fox::Quaternion{ 1.0f, 0.0f, 0.0f, 0.0f };
    }
}
