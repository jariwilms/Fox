#pragma once

#include <span>
#include <type_traits>
#include <memory>

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





        //https://stackoverflow.com/a/21028912
        //This allocator allows you to resize a vector without initializing new memory
        //It is useful for allowing a third party to overwrite the vectors data
        template<typename T, typename A = std::allocator<T>>
        class no_init_allocator : public A
        {
        public:
            using traits_t = std::allocator_traits<A>;
            using A::A;

            template<typename U> 
            struct rebind
            {
                using other = no_init_allocator<U, typename traits_t::template rebind_alloc<U>>;
            };

            template<typename U>
            void construct(U* pointer) noexcept(std::is_nothrow_default_constructible<U>::value)
            {
                ::new (static_cast<void*>(pointer)) U;
            }
            template<typename U, typename...Args>
            void construct(U* pointer, Args&&... args)
            {
                traits_t::construct(static_cast<A&>(*this), pointer, std::forward<Args>(args)...);
            }
        };
    }
}
