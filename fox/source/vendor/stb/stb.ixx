module;

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

export module vendor.stb;

import std;

import fox.core.types.fundamental;
import fox.core.types.common;

export namespace stb
{
    using ::stbi_flip_vertically_on_write;
    using ::stbi_image_free;
    using ::stbi_load_16_from_memory;
    using ::stbi_load_from_memory;
    using ::stbi_loadf_from_memory;
    using ::stbi_set_flip_vertically_on_load;
    using ::stbi_write_bmp_to_func;
    using ::stbi_write_hdr_to_func;
    using ::stbi_write_jpg_to_func;
    using ::stbi_write_png_to_func;

    template<typename T>
    void write_function(fox::void_t* context, fox::void_t* data, fox::int32_t size)
    {
              auto* ctx     = std::bit_cast<std::vector<T>*>(context);
        const auto* pointer = std::bit_cast<const T*>(data);
              auto  span    = std::span{ pointer, static_cast<fox::size_t>(size) };

        ctx->append_range(span);
    }
}
