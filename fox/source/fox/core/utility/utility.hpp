#pragma once

#include <stdafx.hpp>

#include <fox/core/types/common/common.hpp>
#include <fox/core/types/fundamental/fundamental.hpp>

namespace fox
{
    inline namespace utl
    {
        template<typename T>
        static constexpr auto size_of()
        {
            return sizeof(T);
        }
        template<typename T>
        static constexpr auto size_of(const T& value)
        {
            return sizeof(value);
        }
        template<typename T, auto MEMBER_PTR>
        static constexpr auto offset_of()
        {
            return reinterpret_cast<fox::size_t>(
                &reinterpret_cast<const volatile fox::byte_t&>(
                    ((static_cast<T*>(nullptr))->*MEMBER_PTR)));
        }



        template<typename T, fox::size_t EXTENT = std::dynamic_extent>
        auto as_bytes(std::span<const T, EXTENT> span)
        {
            return std::span{ reinterpret_cast<const fox::byte_t*>(span.data()), span.size_bytes() };
        }
        template<typename T>
        auto as_bytes(const T& container)
        {
            return as_bytes(std::span{ container });
        }



        template <typename T>
        static constexpr auto to_underlying(T value) noexcept
        {
            return static_cast<std::underlying_type_t<T>>(value);
        }
    }
}
