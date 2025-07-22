export module fox.core.memory.adapter.no_init;

import std;
import fox.core.types;

export namespace fox::memory::adapter
{
    //A specialized allocator that bypasses initialization when a vector is resized.
    //This allows for direct population of the raw, uninitialized memory.
    //It can significantly improve performance for large allocations by eliminating redundant initialization.
    //https://stackoverflow.com/a/21028912
    //https://www.boost.org/doc/libs/1_75_0/boost/core/noinit_adaptor.hpp
    template<typename A>
    class no_init : public A
    {
    public:
        template<typename U> 
        struct rebind
        {
            using other = adapter::no_init<typename std::allocator_traits<A>::template rebind_alloc<U>>;
        };

        template<typename U>
        void construct(U* pointer) noexcept(std::is_nothrow_default_constructible<U>::value)
        {
            ::new(static_cast<void*>(pointer)) U;
        }
        template<typename U, typename...Args>
        void construct(U* pointer, Args&&... args)
        {
            std::allocator_traits<A>::construct(static_cast<A&>(*this), pointer, std::forward<Args>(args)...);
        }

        template<class U>
        void destroy(U* pointer)
        {
            pointer->~U();
        }

        template<class T, class U>
        friend auto operator==(const adapter::no_init<T>& left, const adapter::no_init<U>& right) noexcept -> fox::bool_t
        {
            return static_cast<const T&>(left) == static_cast<const U&>(right);
        }
        template<class T, class U>
        friend auto operator!=(const adapter::no_init<T>& left, const adapter::no_init<U>& right) noexcept -> fox::bool_t
        {
            return !(left == right);
        }
    };

}
