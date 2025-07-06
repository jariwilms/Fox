#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace fox
{
    using Quaternion = glm::quat;

    namespace quaternion
    {
        constexpr auto identity = fox::Quaternion{ 1.0f, 0.0f, 0.0f, 0.0f };
    }
}
