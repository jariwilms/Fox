export module fox.rendering.api.opengl.utility;

import std;

import fox.rendering.api.opengl.types;

export namespace fox::gfx::api::gl
{
    template<typename T>
    inline constexpr auto to_underlying    (      T        value) noexcept -> std::underlying_type_t<T>
    {
        return static_cast<std::underlying_type_t<T>>(value);
    }
    template<typename T>
    inline constexpr auto to_underlying_ptr(      T* const value) noexcept -> std::underlying_type_t<T>* const
    {
        return std::bit_cast<std::underlying_type_t<T>* const>(value);
    }
    template<typename T>
    inline constexpr auto to_underlying_ptr(const T* const value) noexcept -> const std::underlying_type_t<T>* const
    {
        return std::bit_cast<const std::underlying_type_t<T>* const>(value);
    }



    template<template<typename> typename C, typename T, typename U>
    inline constexpr auto compare(T&& left, U&& right) -> gl::bool_t
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



    template<typename T>
    inline constexpr auto convert_range(gl::range_t     range) -> gl::byterange_t
    {
        return gl::byterange_t{ static_cast<gl::size_t>(range.count * sizeof(T)), static_cast<gl::offset_t>(range.index * sizeof(T)) };
    }
    template<typename T>
    inline constexpr auto convert_range(gl::byterange_t range) -> gl::range_t
    {
        return gl::range_t{ static_cast<gl::count_t>(range.size / sizeof(T)), static_cast<gl::index_t>(range.offset / sizeof(T)) };
    }

    inline constexpr auto range_overlaps(gl::range_t     first, gl::range_t     second) -> gl::bool_t
    {
        return (first.index < second.index + second.count) and (second.index < first.index + second.count);
    }
    inline constexpr auto range_overlaps(gl::byterange_t first, gl::byterange_t second) -> gl::bool_t
    {
        return (first.offset < second.offset + second.size) and (second.offset < first.offset + second.size);
    }



    template<typename T> requires std::is_integral_v<T> and std::is_unsigned_v<T>
    inline constexpr auto to_positive_signed_integral(T value) -> std::make_signed_t<T>
    {
        constexpr auto bitsize = sizeof(T) * 8u;
        constexpr auto mask    = ~(static_cast<T>(1u) << (bitsize - 1u));
                  auto result  = value & mask;

        return static_cast<std::make_signed_t<T>>(result);
    }



    template<typename T, gl::size_t EXTENT = std::dynamic_extent>
    inline constexpr auto as_bytes(std::span<const T, EXTENT> span) -> std::span<const gl::byte_t>
    {
        return std::span{ reinterpret_cast<const gl::byte_t*>(span.data()), span.size_bytes() };
    }
    template<typename T>
    inline constexpr auto as_bytes(const T& container) -> std::span<const gl::byte_t>
    {
        return as_bytes(std::span{ container });
    }



    inline void todo()
    {
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }



    template<typename... Ts>
    struct overload : Ts... { using Ts::operator()...; };
}
