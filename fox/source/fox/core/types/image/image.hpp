#pragma once

#include <span>
#include <vector>
#include <stdexcept>

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

#include <fox/config/config.hpp>
#include <fox/core/types/common/common.hpp>
#include <fox/core/types/linear_algebra/vector.hpp>

namespace fox
{
    class Image
    {
    public:
        enum class Extension
        {
            BMP, 
            JPEG, 
            PNG, 
            HDR, 
        };
        enum class Format
        {
            R8, 
            RG8, 
            RGB8, 
            RGBA8, 

            R16, 
            RG16, 
            RGB16, 
            RGBA16, 

            RGB16_FLOAT,
            RGBA16_FLOAT,

            RGB32_FLOAT, 
            RGBA32_FLOAT, 
        };

        Image(Format format, const fox::Vector2u& dimensions, std::span  <const fox::byte_t>   data)
            : format_{ format }, dimensions_{ dimensions }, data_{ data.begin(), data.end() } {}
        Image(Format format, const fox::Vector2u& dimensions, std::vector<      fox::byte_t>&& data)
            : format_{ format }, dimensions_{ dimensions }, data_{ std::move(data) } {}

        static void encode(Extension extension, fox::Image const& image)
        {
            throw std::logic_error{ "The method or operation has not been implemented!" };
        }
        static auto decode(Format format, std::span<const fox::byte_t> data) -> fox::Image
        {
            enum class Type
            {
                Byte,
                Float,
            };

            auto const& type        = std::invoke([](Format format)
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

                }, format);
            auto const& bpc         = std::invoke([](Format format)
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
                }, format);
            auto const& channels    = std::invoke([](Format format)
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
                }, format);

            void      * pointer     = nullptr;
            auto        iChannels   = fox::int32_t{};
            auto        iDimensions = fox::Vector2i{};
            
            stbi_set_flip_vertically_on_load(cfg::FLIP_IMAGES);
            if (type == Type::Byte  and bpc ==  8u) pointer = stbi_load_from_memory   (data.data(), static_cast<fox::int32_t>(data.size_bytes()), &iDimensions.x, &iDimensions.y, &iChannels, channels);
            if (type == Type::Byte  and bpc == 16u) pointer = stbi_load_16_from_memory(data.data(), static_cast<fox::int32_t>(data.size_bytes()), &iDimensions.x, &iDimensions.y, &iChannels, channels);
            if (type == Type::Float               ) pointer = stbi_loadf_from_memory  (data.data(), static_cast<fox::int32_t>(data.size_bytes()), &iDimensions.x, &iDimensions.y, &iChannels, channels);

            auto      * bytePointer   = reinterpret_cast<fox::byte_t*>(pointer);
            auto const& bytesPerPixel = channels * (bpc / (sizeof(fox::byte_t) * 8u));
            auto const& totalSize     = bytesPerPixel * iDimensions.x * iDimensions.y;

            std::vector<fox::byte_t> v{ bytePointer, bytePointer + totalSize };
            stbi_image_free(pointer);

            return fox::Image{ format, static_cast<fox::Vector2u>(iDimensions), std::move(v) };
        }

        auto format    () const -> Format
        {
            return format_;
        }
        auto dimensions() const -> const fox::Vector2u&
        {
            return dimensions_;
        }
        auto data      () -> std::span<fox::byte_t>
        {
            return data_;
        }
        auto data      () const -> std::span<const fox::byte_t> 
        {
            return data_;
        }

    private:
        fox::Image::Format       format_;
        fox::Vector2u            dimensions_;
        std::vector<fox::byte_t> data_;
    };
}
