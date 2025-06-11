#pragma once

#include <span>

#include <fox/core/types/common/common.hpp>
#include <fox/core/types/linear_algebra/vector.hpp>

namespace fox
{
    constexpr auto FLIP_IMAGES = true; //TODO => config

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
            : m_format{ format }, m_dimensions{dimensions}, m_data{data.begin(), data.end()} { }
        Image(Format format, const fox::Vector2u& dimensions, std::vector<      fox::byte_t>&& data)
            : m_format{ format }, m_dimensions{ dimensions }, m_data{ std::move(data) } {}

        static void encode(Extension extension, const Image& image);
        static auto decode(Format format, std::span<const fox::byte_t> data) -> fox::Image;

        auto format    () const -> Format
        {
            return m_format;
        }
        auto dimensions() const -> const fox::Vector2u&
        {
            return m_dimensions;
        }
        auto data      () -> std::span<fox::byte_t>
        {
            return m_data;
        }
        auto data      () const -> std::span<const fox::byte_t> 
        {
            return m_data;
        }

    private:
        fox::Image::Format       m_format{};
        fox::Vector2u            m_dimensions{};
        std::vector<fox::byte_t> m_data{};
    };
}
