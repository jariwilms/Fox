#include "stdafx.hpp"

#include "Helix/Core/Include/STB.hpp"

#include "Image.hpp"

namespace hlx
{
    struct Context
    {
        std::vector<byte>& data;
    };
    void write_func(void* context, void* data, int size)
    {
        const auto* ctx = reinterpret_cast<Context*>(context);
        const auto* imageData = reinterpret_cast<const byte*>(data);

        ctx->data = std::vector<byte>{ imageData, imageData + size };
    }

    std::vector<byte> Image::encode(Format format, const Image& image)
    {
        stbi_flip_vertically_on_write(Config::IO::flipImages); //Use as parameter?

        const auto& dimensions = image.dimensions();
        const auto& channels = static_cast<int>(image.layout());
        const auto* data = image.data().data();

        std::vector<byte> v{};
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
    Image             Image::decode(Layout layout, std::span<const byte> data)
    {
        stbi_set_flip_vertically_on_load(Config::IO::flipImages);

        int x{}, y{}, c{}, channels{ static_cast<int>(layout) };
        auto* decodedData = reinterpret_cast<byte*>(stbi_load_from_memory(data.data(), static_cast<int>(data.size_bytes()), &x, &y, &c, channels));

        const auto& size = x * y * channels;
        std::vector<byte> v{ decodedData, decodedData + size };

        stbi_image_free(decodedData);

        return Image{ layout, Vector2u{ static_cast<std::uint32_t>(x), static_cast<std::uint32_t>(y) }, std::move(v) };
    }
}
