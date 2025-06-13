#pragma once

#include <span>
#include <vector>
#include <stdexcept>

#include <vendor/stb/stb.hpp>

#include <fox/config/config.hpp>
#include <fox/core/types/common/common.hpp>
#include <fox/core/types/linear_algebra/vector.hpp>
#include <fox/math/constants/constants.hpp>
#include <fox/core/utility/utility.hpp>

namespace fox
{
    class Image
    {
    public:
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
        enum class Channels
        {
            _1 = 1u, 
            _2 = 2u, 
            _3 = 3u, 
            _4 = 4u, 
        };
        enum class Extension
        {
            BMP, 
            JPEG, 
            PNG, 
            HDR, 
        };

        Image(Format format, Channels channels, const fox::Vector2u& dimensions, std::span  <const fox::byte_t>   data)
            : format_{ format }, channels_{ channels }, dimensions_{ dimensions }, data_{ data.begin(), data.end() } {}
        Image(Format format, Channels channels, const fox::Vector2u& dimensions, std::vector<      fox::byte_t>&& data)
            : format_{ format }, channels_{ channels }, dimensions_{ dimensions }, data_{ std::move(data) } {}

        static auto encode(fox::Image const& image, Extension extension) -> std::vector<fox::byte_t>
        {
            stbi_flip_vertically_on_write(cfg::FLIP_IMAGES);

            auto const& write_bmp  = [](const fox::Image& image) -> std::vector<fox::byte_t>
                {
                    return {};
                };
            auto const& write_jpeg = [](const fox::Image& image) -> std::vector<fox::byte_t>
                {
                    return {};
                };
            auto const& write_png  = [](const fox::Image& image) -> std::vector<fox::byte_t>
                {
                          auto  vector     = std::vector<fox::byte_t>{};
                    const auto& dimensions = image.dimensions();

                    stbi_write_png_to_func(
                        vendor::stb::write_function, 
                        &vector, dimensions.x, dimensions.y, 
                        fox::to_underlying(image.channels()), 
                        image.data().data(), 
                        fox::to_underlying(image.channels()) * dimensions.x);

                    return vector;
                };
            auto const& write_hdr  = [](const fox::Image& image) -> std::vector<fox::byte_t>
                {
                    return {};
                };

            switch (extension)
            {
                case Extension::BMP : return std::invoke(write_bmp , image);
                case Extension::JPEG: return std::invoke(write_jpeg, image);
                case Extension::PNG : return std::invoke(write_png , image);
                case Extension::HDR : return std::invoke(write_hdr , image);
            }
        }
        static auto decode(Format format, std::span<const fox::byte_t> data) -> fox::Image
        {
            enum class Type
            {
                Byte,
                Float,
            };

            const auto& type        = std::invoke([](Format format)
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
                        
                        default: throw std::invalid_argument{ "Invalid format!" };
                    };
                }, format);
            const auto& channels    = std::invoke([](Format format)
                {
                    switch (format)
                    {
                        case Format::R8:
                        case Format::R16:          return Channels::_1;

                        case Format::RG8:
                        case Format::RG16:         return Channels::_2;

                        case Format::RGB8:
                        case Format::RGB16:
                        case Format::RGB16_FLOAT:
                        case Format::RGB32_FLOAT:  return Channels::_3;

                        case Format::RGBA8:
                        case Format::RGBA16:
                        case Format::RGBA16_FLOAT:
                        case Format::RGBA32_FLOAT: return Channels::_4;
                        
                        default: throw std::invalid_argument{ "Invalid format!" };
                    };
                }, format);
            const auto& bpc         = std::invoke([](Format format)
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

                        default: throw std::invalid_argument{ "Invalid format!" };
                    };
                }, format);
            
                  void* iPointer    = nullptr;
                  auto  iChannels   = fox::int32_t{};
                  auto  iDimensions = fox::Vector2i{};
            
            stbi_set_flip_vertically_on_load(cfg::FLIP_IMAGES);
            if (type == Type::Byte  and bpc ==  8u) iPointer = stbi_load_from_memory   (data.data(), static_cast<fox::int32_t>(data.size_bytes()), &iDimensions.x, &iDimensions.y, &iChannels, fox::to_underlying(channels));
            if (type == Type::Byte  and bpc == 16u) iPointer = stbi_load_16_from_memory(data.data(), static_cast<fox::int32_t>(data.size_bytes()), &iDimensions.x, &iDimensions.y, &iChannels, fox::to_underlying(channels));
            if (type == Type::Float               ) iPointer = stbi_loadf_from_memory  (data.data(), static_cast<fox::int32_t>(data.size_bytes()), &iDimensions.x, &iDimensions.y, &iChannels, fox::to_underlying(channels));

                  auto* pointer       = reinterpret_cast<const fox::byte_t*>(iPointer);
            const auto& bytesPerPixel = fox::to_underlying(channels) * (bpc / (sizeof(fox::byte_t) * 8u));
            const auto& totalSize     = bytesPerPixel * iDimensions.x * iDimensions.y;

            std::vector<fox::byte_t> v{ pointer, pointer + totalSize };
            stbi_image_free(iPointer);

            return fox::Image{ format, channels, static_cast<fox::Vector2u>(iDimensions), std::move(v) };
        }

        auto format    () const -> Format
        {
            return format_;
        }
        auto channels  () const
        {
            return channels_;
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
        Format                   format_;
        Channels                 channels_;
        fox::Vector2u            dimensions_;
        std::vector<fox::byte_t> data_;
    };
}
