#pragma once

#include <fox/core/types/math/linear_algebra/matrix.hpp>
#include <fox/core/types/math/linear_algebra/quaternion.hpp>
#include <fox/core/types/math/linear_algebra/vector.hpp>
#include <fox/core/types/math/math.hpp>

import vendor.glm;

namespace fox::math
{
    inline namespace trigonometry
    {
        template<typename T>
        inline constexpr auto sin(const T& value) -> T
        {
            return glm::sin(value);
        }
        template<typename T>
        inline constexpr auto cos(const T& value) -> T
        {
            return glm::cos(value);
        }
        template<typename T>
        inline constexpr auto tan(const T& value) -> T
        {
            return glm::tan(value);
        }

        template<typename T>
        inline constexpr auto asin(const T& value) -> T
        {
            return glm::asin(value);
        }
        template<typename T>
        inline constexpr auto acos(const T& value) -> T
        {
            return glm::acos(value);
        }
        template<typename T>
        inline constexpr auto atan(const T& value) -> T
        {
            return glm::atan(value);
        }

        template<typename T>
        inline constexpr auto sinh(const T& value) -> T
        {
            return glm::sinh(value);
        }
        template<typename T>
        inline constexpr auto cosh(const T& value) -> T
        {
            return glm::cosh(value);
        }
        template<typename T>
        inline constexpr auto tanh(const T& value) -> T
        {
            return glm::tanh(value);
        }

        template<typename T>
        inline constexpr auto asinh(const T& value) -> T
        {
            return glm::asinh(value);
        }
        template<typename T>
        inline constexpr auto acosh(const T& value) -> T
        {
            return glm::acosh(value);
        }
        template<typename T>
        inline constexpr auto atanh(const T& value) -> T
        {
            return glm::atanh(value);
        }

        template<typename T>
        inline constexpr auto to_degrees(const T& value) -> T
        {
            return glm::degrees(value);
        }
        template<typename T>
        inline constexpr auto to_radians(const T& value) -> T
        {
            return glm::radians(value);
        }

        inline           auto euler_angles(const fox::Quaternion& value) -> fox::Vector3f
        {
            return glm::eulerAngles(value);
        }

        template<typename T, fox::uint32_t N>
        inline constexpr auto look_at(const fox::Vector<T, N>& direction, const fox::Vector<T, N>& up) -> fox::Quaternion
        {
            return glm::quatLookAt(direction, up);
        }
    }
}
