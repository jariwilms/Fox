export module fox.math.bitwise;

import std;
import fox.core.types;
import fox.core.utility;

export namespace fox::math::bitwise
{
    enum class bit
    {
        zero, 
        one, 
    };
    enum class significance
    {
        least, 
        most, 
    };
    enum class rotation
    {
        left, 
        right, 
    };
    enum class endian
    {
        little, 
        big, 
    };

    template<std::unsigned_integral T>
    constexpr auto and_       (T first, T second) -> T
    {
        return first bitand second;
    }
    template<std::unsigned_integral T>
    constexpr auto or_        (T first, T second) -> T
    {
        return first bitor second;
    }
    template<std::unsigned_integral T>
    constexpr auto xor_       (T first, T second) -> T
    {
        return first xor second;
    }
    template<std::unsigned_integral T>
    constexpr auto compl_     (T first) -> T
    {
        return compl first;
    }

    template<std::unsigned_integral T>
    constexpr auto all        (T value, fox::size_t position) -> fox::bool_t
    {
        return std::bitset<fox::bit_size_of<T>()>{ value }.all();
    }
    template<std::unsigned_integral T>
    constexpr auto any        (T value, fox::size_t position) -> fox::bool_t
    {
        return std::bitset<fox::bit_size_of<T>()>{ value }.any();
    }
    template<std::unsigned_integral T>
    constexpr auto none       (T value, fox::size_t position) -> fox::bool_t
    {
        return std::bitset<fox::bit_size_of<T>()>{ value }.none();
    }

    template<std::unsigned_integral T>
    constexpr auto test       (T value, fox::size_t position) -> fox::bool_t
    {
        return std::bitset<fox::bit_size_of<T>()>{ value }.test(position);
    }
    template<std::unsigned_integral T>
    constexpr auto set        (T value, fox::size_t position) -> T
    {
        return static_cast<T>(std::bitset<fox::bit_size_of<T>()>{ value }.set(position).to_ullong());
    }
    template<std::unsigned_integral T>
    constexpr auto clear      (T value, fox::size_t position) -> T
    {
        return static_cast<T>(std::bitset<fox::bit_size_of<T>()>{ value }.reset(position).to_ullong());
    }
    template<std::unsigned_integral T>
    constexpr auto flip       (T value, fox::size_t position) -> T
    {
        return static_cast<T>(std::bitset<fox::bit_size_of<T>()>{ value }.flip(position).to_ullong());
    }

    template<std::unsigned_integral T>
    constexpr auto count      (T value) -> fox::size_t
    {
        return std::bitset<fox::bit_size_of<T>()>{ value }.count();
    }
    template<bitwise::rotation R, std::unsigned_integral T>
    constexpr auto rotate     (T value, fox::size_t rotation) -> T
    {
        if constexpr (R == bitwise::rotation::left ) return static_cast<T>((std::bitset<fox::bit_size_of<T>()>{ value } << rotation).to_ullong());
        if constexpr (R == bitwise::rotation::right) return static_cast<T>((std::bitset<fox::bit_size_of<T>()>{ value } << rotation).to_ullong());
    }
    template<bitwise::bit B, bitwise::significance S, typename T>
    constexpr auto consecutive(T value) -> fox::size_t
    {
        if constexpr (B == bitwise::bit::zero and S == bitwise::significance::least) return std::countr_zero(value);
        if constexpr (B == bitwise::bit::one  and S == bitwise::significance::least) return std::countr_one (value);
        if constexpr (B == bitwise::bit::zero and S == bitwise::significance::most ) return std::countl_zero(value);
        if constexpr (B == bitwise::bit::one  and S == bitwise::significance::most ) return std::countl_one (value);
    }

    template<std::unsigned_integral T, std::unsigned_integral U>
    constexpr auto set_mask   (T value, U mask) -> T
    {
        return static_cast<T>((std::bitset<fox::bit_size_of<T>()>{ value } |= mask).to_ullong());
    }
    template<std::unsigned_integral T, std::unsigned_integral U>
    constexpr auto clear_mask (T value, U mask) -> T
    {
        return static_cast<T>((std::bitset<fox::bit_size_of<T>()>{ value } bitand std::bitset<fox::bit_size_of<T>()>{ mask }.flip()).to_ullong());
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
        return bitwise::and_(bitwise::count(value), T{ 1u });
    }

    template <class T, class U>
    constexpr auto cast       (const U& value) noexcept -> T 
    {
        return std::bit_cast<T>(value);
    }
}
