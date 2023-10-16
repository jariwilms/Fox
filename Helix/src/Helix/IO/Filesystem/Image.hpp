#pragma once

#include "stdafx.hpp"

#pragma warning(push)
#pragma warning(disable: 6262 26827 26819 26451)
#include <stb_image.h>
#pragma warning(pop)

#include "File.hpp"

namespace hlx
{
    class Image
    {
    public:
        Image(const Vector2u& dimensions, unsigned int channels, const std::vector<byte>& data)
            : m_dimensions{ dimensions }, m_channels{ channels }, m_data{ data } {}
        Image(const Vector2u& dimensions, unsigned int channels, std::vector<byte>&& data)
            : m_dimensions{ dimensions }, m_channels{ channels }, m_data{ std::move(data) } {}

        virtual ~Image() = default;

        static Image decode(std::span<const byte> data, unsigned int channels = 0u)
        {
            stbi_set_flip_vertically_on_load(Config::IO::flipImages);
            channels = std::min(channels, 4u);

            int x{}, y{}, c{};
            auto* decodedData = reinterpret_cast<byte*>(stbi_load_from_memory(data.data(), static_cast<int>(data.size_bytes()), &x, &y, &c, channels));

            const auto& size = x * y * channels;
            std::vector<byte> a{ decodedData, decodedData + size };
            stbi_image_free(decodedData);

            return Image{ Vector2u{ x, y }, channels, std::move(a)};
        }

        size_t size() const
        {
            return data().size_bytes();
        }

        const Vector2u&       dimensions() const
        {
            return m_dimensions;
        }
        unsigned int          channels()   const
        {
            return m_channels;
        }
        std::span<const byte> data()       const
        {
            return m_data;
        }

    private:
        Vector2u          m_dimensions{};
        unsigned int      m_channels{};
        std::vector<byte> m_data{};
    };
}
