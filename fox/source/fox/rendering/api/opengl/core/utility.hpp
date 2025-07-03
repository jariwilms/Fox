#pragma once

#include <stdafx.hpp>

#include <fox/rendering/api/opengl/core/types.hpp>

namespace fox::gfx::api::gl
{
    template<typename T>
    static constexpr auto to_underlying    (      T        value) noexcept -> std::underlying_type_t<T>
    {
        return static_cast<std::underlying_type_t<T>>(value);
    }
    template<typename T>
    static constexpr auto to_underlying_ptr(      T* const value) noexcept ->       std::underlying_type_t<T>* const
    {
        return reinterpret_cast<std::underlying_type_t<T>* const>(value);
    }
    template<typename T>
    static constexpr auto to_underlying_ptr(const T* const value) noexcept -> const std::underlying_type_t<T>* const
    {
        return reinterpret_cast<const std::underlying_type_t<T>* const>(value);
    }

    template<template<typename> typename C, typename T>
    static constexpr auto compare(const T& left, const T& right) -> gl::bool_t
    {
        return C<T>{}(left, right);
    }
    template<template<typename> typename C, typename T, typename U>
    static constexpr auto compare(const T& left, const U& right) -> gl::bool_t
    {
        return C<void>{}(left, right);
    }

    template<typename T>
    static constexpr auto convert_range(gl::range_t     range) -> gl::byterange_t
    {
        return gl::byterange_t{ static_cast<gl::size_t>(range.count * sizeof(T)), static_cast<gl::offset_t>(range.index * sizeof(T)) };
    }
    template<typename T>
    static constexpr auto convert_range(gl::byterange_t range) -> gl::range_t
    {
        return gl::range_t{ static_cast<gl::count_t>(range.size / sizeof(T)), static_cast<gl::index_t>(range.offset / sizeof(T)) };
    }

    template<typename T> requires std::is_integral_v<T> and std::is_unsigned_v<T>
    static constexpr auto to_positive_signed_integral(T value) -> std::make_signed_t<T>
    {
        constexpr auto bitsize = sizeof(T) * 8u;
        constexpr auto mask    = ~(static_cast<T>(1u) << (bitsize - 1u));
                  auto result  = value & mask;

        return static_cast<std::make_signed_t<T>>(result);
    }

    template<typename T, gl::size_t EXTENT = std::dynamic_extent>
    static constexpr auto as_bytes(std::span<const T, EXTENT> span)
    {
        return std::span{ reinterpret_cast<const gl::byte_t*>(span.data()), span.size_bytes() };
    }
    template<typename T>
    static constexpr auto as_bytes(const T& container)
    {
        return as_bytes(std::span{ container });
    }


    static void todo()
    {
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }



    template<typename... Ts>
    struct overload : Ts... { using Ts::operator()...; };
}
