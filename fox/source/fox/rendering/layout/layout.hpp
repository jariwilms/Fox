#pragma once

import std;

import fox.core.types.common;
import fox.core.types.fundamental;
import fox.core.meta.concepts;

namespace fox::gfx
{
    template<typename T, fox::uint32_t N, fox::index_t L = 0u, fox::uint32_t I = 0u> requires (fox::meta::in_closed_interval<N, 1u, 4u>)
    struct attribute_t
    {
        using type = T;

        constexpr auto size           () const -> fox::size_t
        {
            return sizeof(T);
        }
        constexpr auto count          () const -> fox::uint32_t
        {
            return N;
        }
        constexpr auto stride         () const -> fox::size_t
        {
            return size() * count();
        }
        constexpr auto location       () const -> fox::index_t
        {
            return L;
        }
        constexpr auto instancing_rate() const -> fox::uint32_t const
        {
            return I;
        }
    };
    template<typename... T>
    struct layout_t
    {
        constexpr auto stride    () const -> fox::size_t
        {
            auto stride = fox::size_t{};
            std::apply([&](const auto&... element)
                {
                    ((stride += element.stride()), ...);
                }, std::tuple<T...>{});

            return stride;
        }
        constexpr auto attributes() const -> std::tuple<T...>
        {
            return std::tuple<T...>{};
        }
    };
}
