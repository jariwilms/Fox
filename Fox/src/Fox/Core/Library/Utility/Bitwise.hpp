#pragma once

#include "stdafx.hpp"

namespace fox::utl
{
    template<typename T>
    concept BitOperand = std::is_integral_v<T> && (sizeof(T) <= sizeof(i64));
    
    template<typename T>
    constexpr bit bit_query(T value, byte index)                        requires BitOperand<T>
    {
        return (value >> index) & 0x1;
    }
    template<typename T>
    constexpr T   bit_query_v(T value, byte index, byte count)          requires BitOperand<T>
    {
        return (value >> index) & (((T{} + 1) << count) - 1);
    }
    template<typename T>
    constexpr T   bit_mask(T value, byte index, bit state)              requires BitOperand<T>
    {
        return value ^ (-static_cast<T>(state) ^ value) & ((T{} + 1) << index);
    }
    template<typename T, typename U>
    constexpr T   bit_mask_v(T value, U source, byte index, byte count) requires BitOperand<T> && BitOperand<U>
    {
        return (value & ~((((T{} + 1) << count) - 1) << index)) | (static_cast<T>(source) << index);
    }
    template<typename T>
    constexpr T   bit_toggle(T value, byte index)                       requires BitOperand<T>
    {
        return value ^ ((T{} + 1) << index);
    }
}
