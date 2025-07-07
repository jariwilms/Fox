#pragma once

#include <stdafx.hpp>

#include <fox/core/types/common/common.hpp>
#include <fox/core/types/fundamental/fundamental.hpp>

namespace fox
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

        template<template<typename> typename C, typename T>
        inline constexpr auto compare(const T& left, const T& right) -> fox::bool_t
        {
            return C<T>{}(left, right);
        }
        template<template<typename> typename C, typename T, typename U>
        inline constexpr auto compare(const T& left, const U& right) -> fox::bool_t
        {
            return C<void>{}(left, right);
        }

        template<typename T, fox::size_t EXTENT = std::dynamic_extent>
        inline constexpr auto as_bytes(std::span<const T, EXTENT> span)
        {
            return std::span{ reinterpret_cast<const fox::byte_t*>(span.data()), span.size_bytes() };
        }
        template<typename T>
        inline constexpr auto as_bytes(const T& container)
        {
            return as_bytes(std::span{ container });
        }



        template<typename T>
        struct from_inaccessible_ctor : public T
        {
            template<typename... Args>
            from_inaccessible_ctor(Args&&... args)
                : T{ std::forward<Args>(args)... } {}
        };

        template<typename... Ts>
        struct overload : Ts... { using Ts::operator()...; };
    }
}
