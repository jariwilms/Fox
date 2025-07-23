export module fox.math.bitwise;

import std;
import fox.core.types;
import fox.core.utility;

export namespace fox::math::bitwise
{
    enum class e_bit
    {
        zero, 
        one, 
    };
    enum class e_significance
    {
        least, 
        most, 
    };
    enum class e_rotation
    {
        left, 
        right, 
    };
    enum class e_endian
    {
        little, 
        big, 
    };

    template<std::unsigned_integral T>
    constexpr auto all        (T value, fox::size_t position) -> fox::bool_t
    {
        return std::bitset<fox::bit_width<T>()>{ value }.all();
    }
    template<std::unsigned_integral T>
    constexpr auto any        (T value, fox::size_t position) -> fox::bool_t
    {
        return std::bitset<fox::bit_width<T>()>{ value }.any();
    }
    template<std::unsigned_integral T>
    constexpr auto none       (T value, fox::size_t position) -> fox::bool_t
    {
        return std::bitset<fox::bit_width<T>()>{ value }.none();
    }

    template<std::unsigned_integral T>
    constexpr auto test       (T value, fox::size_t position) -> fox::bool_t
    {
        return std::bitset<fox::bit_width<T>()>{ value }.test(position);
    }
    template<std::unsigned_integral T>
    constexpr auto set        (T value, fox::size_t position) -> T
    {
        return static_cast<T>(std::bitset<fox::bit_width<T>()>{ value }.set(position).to_ullong());
    }
    template<std::unsigned_integral T>
    constexpr auto clear      (T value, fox::size_t position) -> T
    {
        return static_cast<T>(std::bitset<fox::bit_width<T>()>{ value }.reset(position).to_ullong());
    }
    template<std::unsigned_integral T>
    constexpr auto flip       (T value, fox::size_t position) -> T
    {
        return static_cast<T>(std::bitset<fox::bit_width<T>()>{ value }.flip(position).to_ullong());
    }

    template<std::unsigned_integral T>
    constexpr auto count      (T value) -> fox::size_t
    {
        return std::bitset<fox::bit_width<T>()>{ value }.count();
    }
    template<bitwise::e_rotation R, std::unsigned_integral T>
    constexpr auto rotate     (T value, fox::size_t rotation) -> T
    {
        if constexpr (R == bitwise::e_rotation::left ) return static_cast<T>((std::bitset<fox::bit_width<T>()>{ value } << rotation).to_ullong());
        if constexpr (R == bitwise::e_rotation::right) return static_cast<T>((std::bitset<fox::bit_width<T>()>{ value } << rotation).to_ullong());
    }
    template<bitwise::e_bit B, bitwise::e_significance S, typename T>
    constexpr auto consecutive(T value) -> fox::size_t
    {
        using enum bitwise::e_bit; 
        using enum bitwise::e_significance;

        if constexpr (B == zero && S == least) return std::countr_zero(value);
        if constexpr (B == one  && S == least) return std::countr_one (value);
        if constexpr (B == zero && S == most ) return std::countl_zero(value);
        if constexpr (B == one  && S == most ) return std::countl_one (value);
    }

    template<std::unsigned_integral T, std::unsigned_integral U>
    constexpr auto set_mask   (T value, U mask) -> T
    {
        return static_cast<T>((std::bitset<fox::bit_width<T>()>{ value } |= mask).to_ullong());
    }
    template<std::unsigned_integral T, std::unsigned_integral U>
    constexpr auto clear_mask (T value, U mask) -> T
    {
        return static_cast<T>((std::bitset<fox::bit_width<T>()>{ value } bitand std::bitset<fox::bit_width<T>()>{ mask }.flip()).to_ullong());
    }

    template<std::unsigned_integral T>
    constexpr auto power_of_2 (T value) -> fox::bool_t
    {
        return std::has_single_bit(value);
    }
    template<std::unsigned_integral T>
    constexpr auto ceiling    (T value) -> T
    {
        return std::bit_ceil(value);
    }
    template<std::unsigned_integral T>
    constexpr auto floor      (T value) -> T
    {
        return std::bit_floor(value);
    }

    template<std::unsigned_integral T>
    constexpr auto parity     (T value) -> T
    {
        return bitwise::count(value) && T{ 1u };
    }

    template <class T, class U>
    constexpr auto cast       (const U& value) noexcept -> T 
    {
        return std::bit_cast<T>(value);
    }
}
