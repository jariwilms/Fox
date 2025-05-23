#include "stdafx.hpp"
#include "Image.hpp"

namespace fox
{
    void fox::Image::encode(Extension extension, const Image& image)
    {
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }
    Image fox::Image::decode(Format format, std::span<const fox::byte_t> data)
    {
        enum class Type
        {
            Byte,
            Float,
        };

        const auto& get_type     = [](Format format)
            {
                switch (format)
                {
                    case Format::R8:
                    case Format::RG8:
                    case Format::RGB8:
                    case Format::RGBA8:

                    case Format::R16:
                    case Format::RG16:
                    case Format::RGB16:
                    case Format::RGBA16:       return Type::Byte;

                    case Format::RGB16_FLOAT:
                    case Format::RGBA16_FLOAT:
                    case Format::RGB32_FLOAT:
                    case Format::RGBA32_FLOAT: return Type::Float;
                };

                throw std::invalid_argument{ "Invalid format!" };

            };
        const auto& get_depth    = [](Format format)
            {
                switch (format)
                {
                    case Format::R8:
                    case Format::RG8:
                    case Format::RGB8:
                    case Format::RGBA8:        return 8u;

                    case Format::R16:
                    case Format::RG16:
                    case Format::RGB16:
                    case Format::RGBA16:
                    case Format::RGB16_FLOAT:
                    case Format::RGBA16_FLOAT: return 16u;

                    case Format::RGB32_FLOAT:
                    case Format::RGBA32_FLOAT: return 32u;
                };

                throw std::invalid_argument{ "Invalid format!" };
            };
        const auto& get_channels = [](Format format)
            {
                switch (format)
                {
                    case Format::R8:
                    case Format::R16:          return 1u;

                    case Format::RG8:
                    case Format::RG16:         return 2u;

                    case Format::RGB8:
                    case Format::RGB16:
                    case Format::RGB16_FLOAT:
                    case Format::RGB32_FLOAT:  return 3u;

                    case Format::RGBA8:
                    case Format::RGBA16:
                    case Format::RGBA16_FLOAT:
                    case Format::RGBA32_FLOAT: return 4u;
                };

                throw std::invalid_argument{ "Invalid format!" };
            };

        stbi_set_flip_vertically_on_load(FLIP_IMAGES);

        void* dataPtr{};
        fox::int32_t  iChannels{};
        fox::Vector2i dimensions{};

        const auto& type     = get_type    (format);
        const auto& depth    = get_depth   (format);
        const auto& channels = get_channels(format);

        if (type == Type::Byte and depth == 8u ) dataPtr = stbi_load_from_memory   (data.data(), static_cast<fox::int32_t>(data.size_bytes()), &dimensions.x, &dimensions.y, &iChannels, channels);
        if (type == Type::Byte and depth == 16u) dataPtr = stbi_load_16_from_memory(data.data(), static_cast<fox::int32_t>(data.size_bytes()), &dimensions.x, &dimensions.y, &iChannels, channels);
        if (type == Type::Float                ) dataPtr = stbi_loadf_from_memory  (data.data(), static_cast<fox::int32_t>(data.size_bytes()), &dimensions.x, &dimensions.y, &iChannels, channels);

              auto* bytePtr       = reinterpret_cast<fox::byte_t*>(dataPtr);
        const auto& bytesPerPixel = channels * (depth / 8u);
        const auto& totalSize     = dimensions.x * dimensions.y * bytesPerPixel;

        std::vector<fox::byte_t> v{ bytePtr, bytePtr + totalSize };
        stbi_image_free(dataPtr);

        return fox::Image{ format, dimensions, std::move(v) };
    }
}
