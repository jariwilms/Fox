#pragma once

#include "stdafx.hpp"

namespace fox
{
    class Image
    {
    public:
        enum class Format
        {
            BMP, 
            JPEG, 
            PNG, 
        };
        enum class Layout
        {
            R8 = 1, 
            RG8, 
            RGB8, 
            RGBA8, 
        };

        Image(Layout layout, const fox::Vector2u& dimensions, std::span<const fox::byte> data)
            : m_layout{ layout }, m_dimensions{ dimensions }, m_data{ data.data(), data.data() + data.size_bytes() }
        {
            const auto& channels  = static_cast<fox::int32_t>(layout);
            const auto& imageSize = static_cast<fox::size_t>(m_dimensions.x) * m_dimensions.y * channels;

            if (imageSize > m_data.size()) throw std::runtime_error{ "Invalid image dimensions or layout!" };
        }
        Image(Layout layout, const fox::Vector2u& dimensions, std::vector<fox::byte>&& data)
            : m_layout{ layout }, m_dimensions{ dimensions }, m_data{ std::move(data) }
        {
            const auto& channels  = static_cast<fox::int32_t>(layout);
            const auto& imageSize = static_cast<fox::size_t>(m_dimensions.x) * m_dimensions.y * channels;

            if (imageSize > m_data.size()) throw std::runtime_error{ "Invalid image dimensions or layout!" };
        }
        virtual ~Image() = default;

        static std::vector<fox::byte> encode(Format format, const Image& image);
        static Image                  decode(Layout layout, std::span<const fox::byte> data);

        Layout                        layout()     const
        {
            return m_layout;
        }
        const fox::Vector2u&          dimensions() const
        {
            return m_dimensions;
        }

        std::span<fox::byte>          data()
        {
            return m_data;
        }
        std::span<const fox::byte>    data() const
        {
            return m_data;
        }

    private:
        Layout                 m_layout{};
        fox::Vector2u          m_dimensions{};
        std::vector<fox::byte> m_data{};
    };
}
