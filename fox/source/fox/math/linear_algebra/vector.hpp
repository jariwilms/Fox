#pragma once

#include <glm/glm.hpp>

#include <fox/core/types/linear_algebra/vector.hpp>

namespace fox::math
{
    template<typename T>
    static constexpr auto dot(const T& first, const T& second) -> fox::fundamental_t<decltype(first.x)>
    {
        return glm::dot(first, second);
    }
}

