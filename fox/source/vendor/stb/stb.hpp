#pragma once

#include <stdafx.hpp>

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

#include <fox/core/types/common/common.hpp>

namespace vendor::stb
{
    template<typename T>
    static void write_function(fox::void_t* context, fox::void_t* data, fox::int32_t size)
    {
              auto* ctx     = reinterpret_cast<std::vector<T>*>(context);
        const auto* pointer = reinterpret_cast<const T*>(data);
              auto  span    = std::span{ pointer, static_cast<fox::size_t>(size) };

        ctx->append_range(span);
    }
}
