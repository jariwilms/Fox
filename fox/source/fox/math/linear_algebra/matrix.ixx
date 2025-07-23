export module fox.math.linear_algebra.matrix;

import std;
import fox.core.types;
import fox.math.linear_algebra.quaternion;
import vendor.glm;

export namespace fox::math
{
    template<typename T, fox::uint32_t N>
    constexpr auto translate(const fox::matrix_t<T, N>& matrix, const fox::vector3f    & translation) -> fox::matrix_t<T, N>
    {
        return glm::translate(matrix, translation);
    }
    template<typename T, fox::uint32_t N>
    constexpr auto rotate   (const fox::matrix_t<T, N>& matrix, const fox::quaternion4f& rotation   ) -> fox::matrix_t<T, N>
    {
        auto angle = glm::angle(rotation);
        auto axis  = glm::axis (rotation);

        return glm::rotate(matrix, angle, axis);
    }
    template<typename T, fox::uint32_t N>
    constexpr auto scale    (const fox::matrix_t<T, N>& matrix, const fox::vector3f    & scale      ) -> fox::matrix_t<T, N>
    {
        return glm::scale(matrix, scale);
    }

    template<typename T, fox::uint32_t N>
              auto transpose(const fox::matrix_t<T, N>& matrix) -> fox::matrix_t<T, N>
    {
        return glm::transpose(matrix);
    }
              auto decompose(const fox::matrix4f      & matrix) -> std::tuple<fox::vector3f, fox::quaternion4f, fox::vector3f, fox::vector3f, fox::vector4f>
    {
        auto  composition                                    = std::tuple<fox::vector3f, fox::quaternion4f, fox::vector3f, fox::vector3f, fox::vector4f>{};
        auto& [position, rotation, scale, skew, perspective] = composition;

        glm::decompose(matrix, scale, rotation, position, skew, perspective);
        rotation = math::conjugate(rotation);

        return composition;
    }
}
