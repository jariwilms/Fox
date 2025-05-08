#include "stdafx.hpp"

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#include "Image.hpp"

namespace fox
{
    constexpr auto FLIP_IMAGES = true; //TODO: => Config

    struct STBContext
    {
        std::vector<fox::byte_t>& data;
    };
    static void write_func(void* context, void* data, int size)
    {
        const auto* ctx       = reinterpret_cast<STBContext*>(context);
        const auto* imageData = reinterpret_cast<const fox::byte_t*>(data);

        ctx->data = std::vector<fox::byte_t>{ imageData, imageData + size };
    }

    std::vector<fox::byte_t> Image::encode(Extension extension, const Image& image)
    {
        stbi_flip_vertically_on_write(FLIP_IMAGES);

        const auto& dimensions = image.dimensions();
        const auto& channels   = fox::to_underlying(image.format());
        const auto* data       = image.data().data();

        std::vector<fox::byte_t> v{};
        STBContext ctx{ v };

        switch (extension)
        {
            case Extension::BMP:  stbi_write_bmp_to_func(write_func, &ctx, dimensions.x, dimensions.y, channels, data);    break;
            case Extension::JPEG: stbi_write_jpg_to_func(write_func, &ctx, dimensions.x, dimensions.y, channels, data, 0); break;
            case Extension::PNG:  stbi_write_png_to_func(write_func, &ctx, dimensions.x, dimensions.y, channels, data, 0); break;

            default: throw std::invalid_argument{ "Invalid extension!" };
        }

        return v;
    }
    Image                    Image::decode(Format format, std::span<const fox::byte_t> data)
    {
        stbi_set_flip_vertically_on_load(FLIP_IMAGES);

        fox::Vector2i dimensions{};

        const auto&  channels   = fox::to_underlying(format);
        const auto&  dataLength = static_cast<fox::int32_t>(data.size_bytes());
              auto*  imageData  = stbi_load_from_memory(data.data(), dataLength, &dimensions.x, &dimensions.y, nullptr, channels);
        const auto&  totalSize  = dimensions.x * dimensions.y * channels;

        std::vector<fox::byte_t> v{ imageData, imageData + totalSize };

        stbi_image_free(imageData);

        return Image{ format, dimensions, std::move(v) };
    }
}
