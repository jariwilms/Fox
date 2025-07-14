export module fox.core.utility;

import std;

import fox.core.types.common;
import fox.core.types.fundamental;

export namespace fox
{
    inline namespace utl
    {
        template<typename T>
        inline constexpr auto size_of()
        {
            return sizeof(T);
        }
        template<typename T>
        inline constexpr auto size_of(const T& value)
        {
            return sizeof(value);
        }
        template<typename T, auto MEMBER_PTR>
        inline constexpr auto offset_of()
        {
            return reinterpret_cast<fox::size_t>(
                &reinterpret_cast<const volatile fox::byte_t&>(
                    ((static_cast<T*>(nullptr))->*MEMBER_PTR)));
        }

        template<template<typename> typename C, typename T, typename U>
        inline constexpr auto compare(T&& left, U&& right) -> fox::bool_t
        {
            if constexpr (std::is_integral_v<T> and std::is_integral_v<U>)
            {
                if (std::is_same_v<C<T>, std::equal_to     <T>>) return std::cmp_equal        (left, right);
                if (std::is_same_v<C<T>, std::not_equal_to <T>>) return std::cmp_not_equal    (left, right);
                if (std::is_same_v<C<T>, std::less         <T>>) return std::cmp_less         (left, right);
                if (std::is_same_v<C<T>, std::greater      <T>>) return std::cmp_greater      (left, right);
                if (std::is_same_v<C<T>, std::less_equal   <T>>) return std::cmp_less_equal   (left, right);
                if (std::is_same_v<C<T>, std::greater_equal<T>>) return std::cmp_greater_equal(left, right);
            }
            else
            {
                if (std::is_same_v<C<T>, std::equal_to     <T>>) return std::ranges::equal_to     {}(std::forward<T>(left), std::forward<U>(right));
                if (std::is_same_v<C<T>, std::not_equal_to <T>>) return std::ranges::not_equal_to {}(std::forward<T>(left), std::forward<U>(right));
                if (std::is_same_v<C<T>, std::less         <T>>) return std::ranges::less         {}(std::forward<T>(left), std::forward<U>(right));
                if (std::is_same_v<C<T>, std::greater      <T>>) return std::ranges::greater      {}(std::forward<T>(left), std::forward<U>(right));
                if (std::is_same_v<C<T>, std::less_equal   <T>>) return std::ranges::less_equal   {}(std::forward<T>(left), std::forward<U>(right));
                if (std::is_same_v<C<T>, std::greater_equal<T>>) return std::ranges::greater_equal{}(std::forward<T>(left), std::forward<U>(right));
            }
        }

        template<std::ranges::range R>
        inline auto as_bytes(R&& range) -> std::span<const fox::byte_t>
        {
            auto span = std::span{ range };
            return std::span<const fox::byte_t>{ std::bit_cast<const fox::byte_t*>(span.data()), span.size_bytes() };
        }
    }
}
