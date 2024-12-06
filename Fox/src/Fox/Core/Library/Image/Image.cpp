#include "stdafx.hpp"

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#include "Image.hpp"

namespace fox
{
    struct Context
    {
        std::vector<fox::byte>& data;
    };
    static void write_func(void* context, void* data, int size)
    {
        const auto* ctx       = reinterpret_cast<Context*>(context);
        const auto* imageData = reinterpret_cast<const fox::byte*>(data);

        ctx->data = std::vector<fox::byte>{ imageData, imageData + size };
    }

    std::vector<fox::byte> Image::encode(Format format, const Image& image)
    {
        stbi_flip_vertically_on_write(Config::IO::flipImages);

        const auto& dimensions = image.dimensions();
        const auto& channels   = static_cast<fox::int32_t>(image.layout());
        const auto* data       = image.data().data();

        std::vector<fox::byte> v{};
        Context ctx{ v };

        switch (format)
        {
            case Format::BMP:  stbi_write_bmp_to_func(write_func, reinterpret_cast<void*>(&ctx), dimensions.x, dimensions.y, channels, data);    break;
            case Format::JPEG: stbi_write_jpg_to_func(write_func, reinterpret_cast<void*>(&ctx), dimensions.x, dimensions.y, channels, data, 0); break;
            case Format::PNG:  stbi_write_png_to_func(write_func, reinterpret_cast<void*>(&ctx), dimensions.x, dimensions.y, channels, data, 0); break;

            default: throw std::invalid_argument{ "Invalid format!" };
        }

        return v;
    }
    Image                  Image::decode(Layout layout, std::span<const fox::byte> data)
    {
        stbi_set_flip_vertically_on_load(Config::IO::flipImages);

        fox::int32_t x{}, y{}, c{}, channels{ static_cast<fox::int32_t>(layout) };
        auto* decodedData = reinterpret_cast<fox::byte*>(stbi_load_from_memory(data.data(), static_cast<fox::int32_t>(data.size_bytes()), &x, &y, &c, channels));

        const auto& size = x * y * channels;
        std::vector<fox::byte> v{ decodedData, decodedData + size };

        stbi_image_free(decodedData);

        return Image{ layout, fox::Vector2u{ static_cast<fox::uint32_t>(x), static_cast<fox::uint32_t>(y) }, std::move(v) };
    }
}
