#pragma once

#include <stdafx.hpp>

namespace fox::gfx::api::gl
{
    template<typename T>
    static constexpr auto to_underlying(T value) noexcept
    {
        return static_cast<std::underlying_type_t<T>>(value);
    }
    template<typename T>
    static constexpr auto to_underlying_ptr(T* value) noexcept
    {
        return reinterpret_cast<std::underlying_type_t<T>*>(value);
    }
    template<typename T>
    static constexpr auto to_underlying_ptr(const T* value) noexcept
    {
        return reinterpret_cast<const std::underlying_type_t<T>*>(value);
    }

    

    template<typename T> requires std::is_integral_v<T> and std::is_unsigned_v<T>
    static constexpr auto as_positive_signed_integral(T value)
    {
        constexpr auto size   = sizeof(T) * 8u;
        constexpr T    mask   = ~(static_cast<T>(1u) << (size - 1u));
                  T    result = value & mask;

        return static_cast<std::make_signed<T>::type>(result);
    }
}
