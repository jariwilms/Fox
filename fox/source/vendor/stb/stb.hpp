#pragma once

#include <span>
#include <vector>

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

#include <fox/core/types/common/common.hpp>

namespace vendor::stb
{
    using context_t = std::vector<fox::byte_t>;

    static void write_function(fox::void_t* context, fox::void_t* data, fox::int32_t size)
    {
        auto* vector  = reinterpret_cast<std::vector<fox::byte_t>*>(context);
        auto* pointer = reinterpret_cast<const fox::byte_t*>(data);
        auto  span    = std::span<const fox::byte_t>{ pointer, pointer + size };

        vector->append_range(span);
    }
}
