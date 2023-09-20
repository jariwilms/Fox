#pragma once

#include "stdafx.hpp"

namespace hlx::utl
{
    //https://stackoverflow.com/questions/70524923/c-convert-any-number-of-nested-vector-of-vector-to-equivalent-vector-of-span
    template<typename T>
    auto to_span(const std::vector<T>& v)
    {
        return std::span{ v };
    }
    template<typename T, typename U>
    std::span<const U> to_span(const std::vector<T>& v)
    {
        return std::span<const U>{ reinterpret_cast<const U*>(v.data()), v.size() * sizeof(U) };
    }
    template<typename T>
    auto to_span(const std::vector<std::vector<T>>& v)
    {
        using value_type = decltype(to_span(v.at(0)));

        std::vector<value_type> r{};
        for (const auto& _ : v)
        {
            r.push_back(to_span(_));
        }

        return to_span(r);
    }

    template<typename T, size_t extent>
    auto as_bytes(std::span<T, extent> s)
    {
        constexpr auto dynamic_extent = static_cast<size_t>(-1); //no idea
        using return_type = std::span<const byte, extent == dynamic_extent ? dynamic_extent : sizeof(T) * extent>;

        return return_type{ reinterpret_cast<const byte*>(s.data()), s.size_bytes() };
    }
}
