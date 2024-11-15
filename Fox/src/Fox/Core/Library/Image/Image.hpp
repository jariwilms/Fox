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

        Image(Layout layout, const Vector2u& dimensions, std::span<const byte> data)
            : m_layout{ layout }, m_dimensions{ dimensions }, m_data{ data.data(), data.data() + data.size_bytes() }
        {
            const auto& channels = static_cast<int>(layout);
            if (static_cast<size_t>(m_dimensions.x) * m_dimensions.y * channels > m_data.size()) throw std::runtime_error{ "Invalid image dimensions or layout!" };
        }
        Image(Layout layout, const Vector2u& dimensions, std::vector<byte>&& data)
            : m_layout{ layout }, m_dimensions{ dimensions }, m_data{ std::move(data) }
        {
            const auto& channels = static_cast<int>(layout);
            if (static_cast<size_t>(m_dimensions.x) * m_dimensions.y * channels > m_data.size()) throw std::runtime_error{ "Invalid image dimensions or layout!" };
        }

        virtual ~Image() = default;

        static std::vector<byte> encode(Format format, const Image& image);
        static Image             decode(Layout layout, std::span<const byte> data);

        Layout                layout()     const
        {
            return m_layout;
        }
        const Vector2u&       dimensions() const
        {
            return m_dimensions;
        }

        std::span<byte>       data()       
        {
            return m_data;
        }
        std::span<const byte> data() const
        {
            return m_data;
        }

    private:
        Layout            m_layout{};
        Vector2u          m_dimensions{};
        std::vector<byte> m_data{};
    };
}
