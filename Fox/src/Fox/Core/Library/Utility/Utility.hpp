#pragma once

#include "stdafx.hpp"

namespace fox::utl
{
    template<typename T, auto MPTR>
    static constexpr auto offset_of()
    {
        return reinterpret_cast<std::size_t>(
            &reinterpret_cast<const volatile char&>(
                ((static_cast<T*>(
                    nullptr))->*MPTR)
                )
            );
    }



    template<typename T, fox::size_t SIZE>
    auto to_span(const std::array<T, SIZE>& v)
    {
        return std::span{ v };
    }



    //https://stackoverflow.com/questions/70524923
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



    template<typename T, fox::size_t EXTENT>
    auto as_bytes(std::span<T, EXTENT> s)
    {
        constexpr auto dynamic_extent = static_cast<fox::size_t>(-1);
        using return_type = std::span<const fox::byte_t, EXTENT == dynamic_extent ? dynamic_extent : sizeof(T) * EXTENT>; //?

        return return_type{ reinterpret_cast<const fox::byte_t*>(s.data()), s.size_bytes() };
    }



    //https://stackoverflow.com/a/21028912
    //There is an instance where we want a vector to take ownership of a large amount of preallocated data without allocation or initialization
    //This allocator does just that; nothing
    template <typename T, typename A = std::allocator<T>>
    class default_init_allocator : public A
    {
        using a_t = std::allocator_traits<A>;
    public:
        template <typename U> 
        struct rebind
        {
            using other = default_init_allocator<U, typename a_t::template rebind_alloc<U>>;
        };

        using A::A;

        template <typename U>
        void construct(U* ptr) noexcept(std::is_nothrow_default_constructible<U>::value)
        {
            ::new (static_cast<void*>(ptr)) U;
        }
        template <typename U, typename...Args>
        void construct(U* ptr, Args&&... args)
        {
            a_t::construct(static_cast<A&>(*this), ptr, std::forward<Args>(args)...);
        }
    };



    //https://stackoverflow.com/a/57053750
    template<typename V>
    void resize(V& v, size_t newSize)
    {
        struct vt { typename V::value_type v; vt() {} };
        static_assert(sizeof(vt[10]) == sizeof(typename V::value_type[10]), "alignment error");
        using V2 = std::vector<vt, typename std::allocator_traits<typename V::allocator_type>::template rebind_alloc<vt>>;
        reinterpret_cast<V2&>(v).resize(newSize);
    }
}
