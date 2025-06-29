#pragma once

#include <fox/core/types/fundamental/fundamental.hpp>
#include <fox/core/types/math/linear_algebra/matrix.hpp>
#include <fox/core/types/math/linear_algebra/vector.hpp>
#include <fox/math/linear_algebra/quaternion.hpp>

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

    static           auto decompose(const fox::Matrix4f& matrix) -> fox::composition_t
    {
        auto position    = fox::Vector3f  {};
        auto rotation    = fox::Quaternion{};
        auto scale       = fox::Vector3f  {};
        auto skew        = fox::Vector3f  {};
        auto perspective = fox::Vector4f  {};

        glm::decompose(matrix, scale, rotation, position, skew, perspective);
        rotation = math::conjugate(rotation);

        return fox::composition_t{ position, rotation, scale, skew, perspective };
    }
}
