#pragma once

#include "stdafx.hpp"

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
        enum class Format : fox::uint32_t
        {
            R8 = 1u, 
            RG8, 
            RGB8, 
            RGBA8, 
        };

        Image(Format format, const fox::Vector2u& dimensions, std::span<const fox::byte_t> data)
        {
            const auto& channels  = fox::to_underlying(format);
            const auto& totalSize = static_cast<fox::size_t>(dimensions.x) * dimensions.y * channels;

            if (totalSize > data.size()) throw std::runtime_error{ "Invalid image format or dimensions!" };

            m_format     = format;
            m_dimensions = dimensions;
            m_data       = { data.begin(), data.end() };
        }
        Image(Format format, const fox::Vector2u& dimensions, std::vector<fox::byte_t>&& data)
        {
            const auto& channels  = fox::to_underlying(format);
            const auto& totalSize = static_cast<fox::size_t>(dimensions.x) * dimensions.y * channels;

            if (totalSize > data.size()) throw std::runtime_error{ "Invalid image format or dimensions!" };

            m_format     = format;
            m_dimensions = dimensions;
            m_data       = std::move(data);
        }

        static std::vector<fox::byte_t> encode(Extension extension, const Image& image);
        static Image                    decode(Format layout, std::span<const fox::byte_t> data);

        Format                          format()     const
        {
            return m_format;
        }
        const fox::Vector2u&            dimensions() const
        {
            return m_dimensions;
        }

        std::span<fox::byte_t>          data()
        {
            return m_data;
        }
        std::span<const fox::byte_t>    data() const
        {
            return m_data;
        }

    private:
        Format                   m_format{};
        fox::Vector2u            m_dimensions{};
        std::vector<fox::byte_t> m_data{};
    };
}
