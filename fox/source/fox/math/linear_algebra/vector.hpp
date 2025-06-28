#pragma once

#include <glm/glm.hpp>

#include <fox/core/types/math/linear_algebra/vector.hpp>

namespace fox::math
{
    template<typename T, fox::uint32_t N>
    static constexpr auto dot(const fox::Vector<T, N>& first, const fox::Vector<T, N>& second) -> fox::fundamental_t<T>
    {
        return glm::dot(first, second);
    }
    template<typename T, fox::uint32_t N>
    static constexpr auto normalize(const fox::Vector<T, N>& value) -> fox::Vector<T, N>
    {
        return glm::normalize(value);
    }
}
