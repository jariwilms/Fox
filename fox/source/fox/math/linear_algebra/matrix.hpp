#pragma once

#include <fox/core/types/fundamental/fundamental.hpp>
#include <fox/core/types/math/linear_algebra/matrix.hpp>

namespace fox::math
{
    template<typename T, fox::uint32_t N>
    static constexpr auto translate(const fox::Matrix<T, N>& matrix, const fox::Vector3f& translation) -> fox::Matrix<T, N>
    {
        return glm::translate(matrix, translation);
    }
    template<typename T, fox::uint32_t N>
    static constexpr auto rotate   (const fox::Matrix<T, N>& matrix, const fox::Vector3f& rotation   ) -> fox::Matrix<T, N>
    {
        return glm::rotate(matrix, rotation);
    }
    template<typename T, fox::uint32_t N>
    static constexpr auto scale    (const fox::Matrix<T, N>& matrix, const fox::Vector3f& scale      ) -> fox::Matrix<T, N>
    {
        return glm::scale(matrix, scale);
    }
}
