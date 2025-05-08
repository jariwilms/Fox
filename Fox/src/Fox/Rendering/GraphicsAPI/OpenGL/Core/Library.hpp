#pragma once

#include "stdafx.hpp"

namespace fox::gfx::api::gl
{
    template<typename T>
    static constexpr auto to_underlying(T value) noexcept
    {
        return static_cast<std::underlying_type_t<T>>(value);
    }
    template<typename T>
    static constexpr auto to_underlying_ptr(T* value)
    {
        return reinterpret_cast<std::underlying_type_t<T>*>(value);
    }
    template<typename T>
    static constexpr auto to_underlying_ptr(const T* value)
    {
        return reinterpret_cast<const std::underlying_type_t<T>*>(value);
    }
}
