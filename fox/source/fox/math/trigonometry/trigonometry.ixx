export module fox.math.trigonometry;

import std;
import fox.core.types;
import vendor.glm;

export namespace fox::math
{
    inline namespace trigonometry
    {
        template<std::floating_point T>
        constexpr auto sin(const T& value) -> T
        {
            return glm::sin(value);
        }
        template<std::floating_point T>
        constexpr auto cos(const T& value) -> T
        {
            return glm::cos(value);
        }
        template<std::floating_point T>
        constexpr auto tan(const T& value) -> T
        {
            return glm::tan(value);
        }

        template<std::floating_point T>
        constexpr auto asin(const T& value) -> T
        {
            return glm::asin(value);
        }
        template<std::floating_point T>
        constexpr auto acos(const T& value) -> T
        {
            return glm::acos(value);
        }
        template<std::floating_point T>
        constexpr auto atan(const T& value) -> T
        {
            return glm::atan(value);
        }

        template<std::floating_point T>
        constexpr auto sinh(const T& value) -> T
        {
            return glm::sinh(value);
        }
        template<std::floating_point T>
        constexpr auto cosh(const T& value) -> T
        {
            return glm::cosh(value);
        }
        template<std::floating_point T>
        constexpr auto tanh(const T& value) -> T
        {
            return glm::tanh(value);
        }

        template<std::floating_point T>
        constexpr auto asinh(const T& value) -> T
        {
            return glm::asinh(value);
        }
        template<std::floating_point T>
        constexpr auto acosh(const T& value) -> T
        {
            return glm::acosh(value);
        }
        template<std::floating_point T>
        constexpr auto atanh(const T& value) -> T
        {
            return glm::atanh(value);
        }

        template<typename T>
        constexpr auto to_degrees(const T& value) -> T
        {
            return glm::degrees(value);
        }
        template<typename T>
        constexpr auto to_radians(const T& value) -> T
        {
            return glm::radians(value);
        }

                  auto euler_angles(const fox::quaternion4f& value) -> fox::vector3f
        {
            return glm::eulerAngles(value);
        }

        template<std::floating_point T, fox::uint32_t N>
        constexpr auto look_at(const fox::vector_t<T, N>& direction, const fox::vector_t<T, N>& up) -> fox::quaternion4f
        {
            return glm::quatLookAt(direction, up);
        }
    }
}
