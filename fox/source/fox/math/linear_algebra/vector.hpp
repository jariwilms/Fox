#pragma once

#include <glm/glm.hpp>

#include <fox/core/types/math/linear_algebra/vector.hpp>

namespace fox::math
{
    template<typename T>
    static constexpr auto dot(const T& first, const T& second) -> fox::fundamental_t<decltype(first.x)>
    {
        return glm::dot(first, second);
    }
    template<typename T, fox::uint32_t N>
    static constexpr auto normalize(const fox::Vector<T, N>& value) -> fox::Vector<T, N>
    {
        return glm::normalize(value);
    }
}

