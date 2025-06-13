#pragma once

#include <glm/glm.hpp>

namespace fox::math
{
    inline namespace trigonometry
    {
        template<typename T> requires (std::is_floating_point_v<T>)
        static constexpr auto sin(T value)
        {
            return glm::sin(value);
        }
        template<typename T> requires (std::is_floating_point_v<T>)
        static constexpr auto cos(T value)
        {
            return glm::cos(value);
        }
        template<typename T> requires (std::is_floating_point_v<T>)
        static constexpr auto tan(T value)
        {
            return glm::tan(value);
        }

        template<typename T> requires (std::is_floating_point_v<T>)
        static constexpr auto asin(T value)
        {
            return glm::asin(value);
        }
        template<typename T> requires (std::is_floating_point_v<T>)
        static constexpr auto acos(T value)
        {
            return glm::acos(value);
        }
        template<typename T> requires (std::is_floating_point_v<T>)
        static constexpr auto atan(T value)
        {
            return glm::atan(value);
        }

        template<typename T> requires (std::is_floating_point_v<T>)
        static constexpr auto sinh(T value)
        {
            return glm::sinh(value);
        }
        template<typename T> requires (std::is_floating_point_v<T>)
        static constexpr auto cosh(T value)
        {
            return glm::cosh(value);
        }
        template<typename T> requires (std::is_floating_point_v<T>)
        static constexpr auto tanh(T value)
        {
            return glm::tanh(value);
        }

        template<typename T> requires (std::is_floating_point_v<T>)
        static constexpr auto asinh(T value)
        {
            return glm::asinh(value);
        }
        template<typename T> requires (std::is_floating_point_v<T>)
        static constexpr auto acosh(T value)
        {
            return glm::acosh(value);
        }
        template<typename T> requires (std::is_floating_point_v<T>)
        static constexpr auto atanh(T value)
        {
            return glm::atanh(value);
        }

        template<typename T> requires (std::is_floating_point_v<T>)
        static constexpr auto to_degrees(T value)
        {
            return glm::degrees(value);
        }
        template<typename T> requires (std::is_floating_point_v<T>)
        static constexpr auto to_radians(T value)
        {
            return glm::radians(value);
        }
    }
}
