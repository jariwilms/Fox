export module fox.core.utility;

import std;
import fox.core.types;

export namespace fox
{
    inline namespace utl
    {
        template<typename T>
        constexpr auto byte_size_of()
        {
            return sizeof(T);
        }
        template<typename T>
        constexpr auto byte_size_of(const T& value)
        {
            return sizeof(value);
        }
        template<typename T>
        constexpr auto bit_size_of (const T& value)
        {
            return utl::byte_size_of(value) * fox::size_t{ 8u };
        }
        template<typename T>
        constexpr auto bit_size_of ()
        {
            return utl::byte_size_of<T>() * fox::size_t{ 8u };
        }
        template<typename T, auto MEMBER_PTR>
        constexpr auto offset_of   ()
        {
            return reinterpret_cast<fox::size_t>(
                &reinterpret_cast<const volatile fox::byte_t&>(
                    ((static_cast<T*>(nullptr))->*MEMBER_PTR)));
        }



        template<template<typename> typename C, typename T, typename U>
        inline constexpr auto compare(T&& left, U&& right) -> fox::bool_t
        {
            if constexpr (std::is_same_v<C<fox::void_t>, std::equal_to     <fox::void_t>>) return std::cmp_equal        (left, right);
            if constexpr (std::is_same_v<C<fox::void_t>, std::not_equal_to <fox::void_t>>) return std::cmp_not_equal    (left, right);
            if constexpr (std::is_same_v<C<fox::void_t>, std::less         <fox::void_t>>) return std::cmp_less         (left, right);
            if constexpr (std::is_same_v<C<fox::void_t>, std::greater      <fox::void_t>>) return std::cmp_greater      (left, right);
            if constexpr (std::is_same_v<C<fox::void_t>, std::less_equal   <fox::void_t>>) return std::cmp_less_equal   (left, right);
            if constexpr (std::is_same_v<C<fox::void_t>, std::greater_equal<fox::void_t>>) return std::cmp_greater_equal(left, right);
        }



        template<std::ranges::range R>
        auto as_bytes(R&& range) -> std::span<const fox::byte_t>
        {
            auto span = std::span{ range };
            return std::span<const fox::byte_t>{ std::bit_cast<const fox::byte_t*>(span.data()), span.size_bytes() };
        }
    }
}
