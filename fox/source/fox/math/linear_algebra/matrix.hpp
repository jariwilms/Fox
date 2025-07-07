#pragma once

#include <fox/core/types/fundamental/fundamental.hpp>
#include <fox/core/types/math/linear_algebra/matrix.hpp>
#include <fox/core/types/math/linear_algebra/vector.hpp>
#include <fox/math/linear_algebra/quaternion.hpp>

namespace fox::math
{
    template<typename T, fox::uint32_t N>
    inline constexpr auto translate(const fox::Matrix<T, N>& matrix, const fox::Vector3f  & translation) -> fox::Matrix<T, N>
    {
        return glm::translate(matrix, translation);
    }
    template<typename T, fox::uint32_t N>
    inline constexpr auto rotate   (const fox::Matrix<T, N>& matrix, const fox::Quaternion& rotation   ) -> fox::Matrix<T, N>
    {
        auto angle = glm::angle(rotation);
        auto axis  = glm::axis (rotation);

        return glm::rotate(matrix, angle, axis);
    }
    template<typename T, fox::uint32_t N>
    inline constexpr auto scale    (const fox::Matrix<T, N>& matrix, const fox::Vector3f  & scale      ) -> fox::Matrix<T, N>
    {
        return glm::scale(matrix, scale);
    }

    inline           auto decompose(const fox::Matrix4f& matrix) -> std::tuple<fox::Vector3f, fox::Quaternion, fox::Vector3f, fox::Vector3f, fox::Vector4f>
    {
        auto  composition                                    = std::tuple<fox::Vector3f, fox::Quaternion, fox::Vector3f, fox::Vector3f, fox::Vector4f>{};
        auto& [position, rotation, scale, skew, perspective] = composition;

        glm::decompose(matrix, scale, rotation, position, skew, perspective);
        rotation = math::conjugate(rotation);

        return composition;
    }
}
