#pragma once

#include "stdafx.hpp"

#pragma warning(push)
#pragma warning(disable: 6262 26827 26819 26451)
#include <stb_image.h>
#pragma warning(pop)

#include "File.hpp"

namespace hlx
{
    //TODO: complete rework
	class Image
	{
	public:
        explicit Image(std::shared_ptr<const std::vector<byte>> data)
            : m_data{ data }
        {
            gather_info();
        }
        explicit Image(std::shared_ptr<File> file)
            : m_data{ file->read() }
        {
            gather_info();
        }

        std::shared_ptr<const std::vector<byte>> read(unsigned int components = 0u)
        {
            stbi_set_flip_vertically_on_load(Config::IO::flipImages);
            components = std::min(components, 4u);

            int x{}, y{}, c{};
            const auto& size      = m_dimensions.x * m_dimensions.y * components;
            const auto& imageData = std::span<byte>{ reinterpret_cast<byte*>(stbi_load_from_memory(m_data->data(), static_cast<int>(m_data->size()), &x, &y, &c, components)), size };

            auto buffer = std::make_unique<const std::vector<byte>>(imageData.begin(), imageData.end());
            stbi_image_free(imageData.data());

            return buffer;
		}

        const Vector2u& dimensions() const
        {
            return m_dimensions;
        }
        unsigned int    channels()   const
        {
            return m_channels;
        }

    private:
        void gather_info()
        {
            int x{}, y{}, c{};
            const auto& success = stbi_info_from_memory(m_data->data(), static_cast<int>(m_data->size()), &x, &y, &c);
            if (!success) throw std::runtime_error{ std::format("Failed to get image properties! reason: {}", stbi_failure_reason()) };

            m_dimensions = { x, y };
            m_channels = c;
        }

        Vector2u     m_dimensions{};
        unsigned int m_channels{};

        std::shared_ptr<const std::vector<byte>> m_data{};
	};
}
