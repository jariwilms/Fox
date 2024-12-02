#pragma once

#include "stdafx.hpp"

namespace fox::utl
{
    template<typename T>
    concept BitOperand = std::is_integral_v<T> && (sizeof(T) <= sizeof(fox::int64_t));
    
    template<typename T>
    constexpr bool bit_query(T value, fox::byte index)                        requires BitOperand<T>
    {
        return (value >> index) & 0x1;
    }
    template<typename T>
    constexpr T   bit_query_v(T value, fox::byte index, fox::byte count)          requires BitOperand<T>
    {
        return (value >> index) & (((T{} + 1) << count) - 1);
    }
    template<typename T>
    constexpr T   bit_mask(T value, fox::byte index, bool state)              requires BitOperand<T>
    {
        return value ^ (-static_cast<T>(state) ^ value) & ((T{} + 1) << index);
    }
    template<typename T, typename U>
    constexpr T   bit_mask_v(T value, U source, fox::byte index, fox::byte count) requires BitOperand<T> && BitOperand<U>
    {
        return (value & ~((((T{} + 1) << count) - 1) << index)) | (static_cast<T>(source) << index);
    }
    template<typename T>
    constexpr T   bit_toggle(T value, fox::byte index)                       requires BitOperand<T>
    {
        return value ^ ((T{} + 1) << index);
    }
}
