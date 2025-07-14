#pragma once

import fox.core.types.math;

import vendor.glm;

namespace fox::math
{
    template<typename T, fox::uint32_t N>
    inline constexpr auto dot(const fox::Vector<T, N>& first, const fox::Vector<T, N>& second) -> fox::fundamental_t<T>
    {
        return glm::dot(first, second);
    }
    template<typename T, fox::uint32_t N>
    inline constexpr auto normalize(const fox::Vector<T, N>& value) -> fox::Vector<T, N>
    {
        return glm::normalize(value);
    }
}
