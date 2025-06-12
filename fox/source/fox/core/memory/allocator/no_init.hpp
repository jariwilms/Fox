#pragma once

#include <memory>

namespace fox::memory
{
    //Allocator that skips initialization when resizing vectors.
    //It allows external code to populate the uninitialized memory directly, 
    //resulting in a fairly large optimisation for larger allocations.
    //https://stackoverflow.com/a/21028912

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
            ::new(static_cast<void*>(pointer)) U;
        }
        template<typename U, typename...Args>
        void construct(U* pointer, Args&&... args)
        {
            traits_t::construct(static_cast<A&>(*this), pointer, std::forward<Args>(args)...);
        }
    };
}
