#pragma once

#include <memory>

namespace fox
{
    template<typename T>
    void memcpst(T* dst, T* src, int value)
    {
        std::memcpy(dst, src, sizeof(T));
        std::memset(&src, value, sizeof(T));
    }
}
