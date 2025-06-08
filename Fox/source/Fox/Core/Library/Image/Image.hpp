#pragma once

#include "stdafx.hpp"

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

namespace fox
{
    constexpr auto FLIP_IMAGES = true;

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

        static void  encode(Extension extension, const Image& image);
        static Image decode(Format format, std::span<const fox::byte_t> data);

        Format                       format    () const
        {
            return m_format;
        }
        const fox::Vector2u&         dimensions() const
        {
            return m_dimensions;
        }
        std::span<fox::byte_t>       data      ()
        {
            return m_data;
        }
        std::span<const fox::byte_t> data      () const
        {
            return m_data;
        }

    private:
        Format                   m_format{};
        fox::Vector2u            m_dimensions{};
        std::vector<fox::byte_t> m_data{};
    };
}
