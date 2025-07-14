#pragma once

#include <fox/core/types/math/math.hpp>

import std;

import fox.config;
import fox.core.types.common;

import vendor.stb;

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

        template<std::ranges::range R>
        Image(Format format, Channels channels, const fox::Vector2u& dimensions, R&& range)
            : format_{ format }, channels_{ channels }, dimensions_{ dimensions }, data_{ std::from_range, std::forward<R>(range) } {}

        template<Extension E>
        static auto encode(const fox::Image& image) -> auto
        {
            stb::stbi_flip_vertically_on_write(cfg::FLIP_IMAGES);

            auto write_bmp  = [](const fox::Image& image) -> std::vector<fox::byte_t>
                {
                          auto  vector     = std::vector<fox::byte_t>{};
                    const auto& dimensions = image.dimensions();

                    stb::stbi_write_bmp_to_func(
                        stb::write_function<fox::byte_t>, 
                        &vector, dimensions.x, dimensions.y, 
                        std::to_underlying(image.channels()), 
                        image.data().data());

                    return vector;
                };
            auto write_jpeg = [](const fox::Image& image) -> std::vector<fox::byte_t>
                {
                          auto  vector     = std::vector<fox::byte_t>{};
                    const auto& dimensions = image.dimensions();

                    stb::stbi_write_jpg_to_func(
                        stb::write_function<fox::byte_t>, 
                        &vector, dimensions.x, dimensions.y, 
                        std::to_underlying(image.channels()), 
                        image.data().data(), fox::int32_t{ 100u });

                    return vector;
                };
            auto write_png  = [](const fox::Image& image) -> std::vector<fox::byte_t>
                {
                          auto  vector     = std::vector<fox::byte_t>{};
                    const auto& dimensions = image.dimensions();

                    stb::stbi_write_png_to_func(
                        stb::write_function<fox::byte_t>, 
                        &vector, dimensions.x, dimensions.y, 
                        std::to_underlying(image.channels()), 
                        image.data().data(), 
                        std::to_underlying(image.channels()) * dimensions.x);

                    return vector;
                };
            auto write_hdr  = [](const fox::Image& image) -> std::vector<fox::float32_t>
                {
                          auto  vector     = std::vector<fox::float32_t>{};
                    const auto& dimensions = image.dimensions();

                    stb::stbi_write_hdr_to_func(
                        stb::write_function<fox::float32_t>, 
                        &vector, dimensions.x, dimensions.y, 
                        std::to_underlying(image.channels()), 
                        std::bit_cast<const fox::float32_t*>(image.data().data()));

                    return vector;
                };

            if constexpr (E == Extension::BMP ) return std::invoke(write_bmp , image);
            if constexpr (E == Extension::JPEG) return std::invoke(write_jpeg, image);
            if constexpr (E == Extension::PNG ) return std::invoke(write_png , image);
            if constexpr (E == Extension::HDR ) return std::invoke(write_hdr , image);
        }
        static auto decode(Format format, std::span<const fox::byte_t> data) -> fox::Image
        {
            enum class Type
            {
                Byte8, 
                Byte16, 
                Float32,
            };

            const auto  type        = std::invoke([](Format format) -> Type
                {
                    switch (format)
                    {
                        case Format::R8:
                        case Format::RG8:
                        case Format::RGB8:
                        case Format::RGBA8:        return Type::Byte8;

                        case Format::R16:
                        case Format::RG16:
                        case Format::RGB16:
                        case Format::RGBA16:       return Type::Byte16;

                        case Format::RGB16_FLOAT:
                        case Format::RGBA16_FLOAT:
                        case Format::RGB32_FLOAT:
                        case Format::RGBA32_FLOAT: return Type::Float32;
                        
                        default: throw std::invalid_argument{ "Invalid format!" };
                    };
                }, format);
            const auto  channels    = std::invoke([](Format format) -> Channels
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
            const auto  bpc         = std::invoke([](Format format) -> fox::uint32_t
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
            
            stb::stbi_set_flip_vertically_on_load(cfg::FLIP_IMAGES);
            if (type == Type::Byte8  ) iPointer = stb::stbi_load_from_memory   (data.data(), static_cast<fox::int32_t>(data.size_bytes()), &iDimensions.x, &iDimensions.y, &iChannels, std::to_underlying(channels));
            if (type == Type::Byte16 ) iPointer = stb::stbi_load_16_from_memory(data.data(), static_cast<fox::int32_t>(data.size_bytes()), &iDimensions.x, &iDimensions.y, &iChannels, std::to_underlying(channels));
            if (type == Type::Float32) iPointer = stb::stbi_loadf_from_memory  (data.data(), static_cast<fox::int32_t>(data.size_bytes()), &iDimensions.x, &iDimensions.y, &iChannels, std::to_underlying(channels));

                  auto  bpp         = std::to_underlying(channels) * (bpc / (sizeof(fox::byte_t) * 8u));
                  auto  span        = std::span{ std::bit_cast<const fox::byte_t*>(iPointer), bpp * iDimensions.x * iDimensions.y };
                  auto  vector      = std::vector<fox::byte_t>{ std::from_range, span };

            stb::stbi_image_free(iPointer);

            return fox::Image{ format, channels, static_cast<fox::Vector2u>(iDimensions), std::move(vector) };
        }

        auto format    () const -> Format
        {
            return format_;
        }
        auto channels  () const -> Channels
        {
            return channels_;
        }
        auto dimensions() const -> const fox::Vector2u&
        {
            return dimensions_;
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
