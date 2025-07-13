#pragma once

#include <stdafx.hpp>

namespace fox
{
    inline namespace meta
    {
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
