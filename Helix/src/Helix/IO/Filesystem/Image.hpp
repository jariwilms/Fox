#pragma once

#include "stdafx.hpp"

#pragma warning(push)
#pragma warning(disable: 6262 26827 26819 26451)
#include <stb_image.h>
#pragma warning(pop)

#include "File.hpp"

namespace hlx
{
	struct Image : public File
	{
	public:
		struct Properties
		{
			Vector2u dimensions{};
			size_t size{};
			unsigned int channels{};
			const std::vector<byte> data{};
		};

		explicit Image(const std::filesystem::path& path)
			: File{ path }
		{
			const auto fileData = File::read();
			stbi_info_from_memory(fileData->data(), static_cast<int>(m_size), reinterpret_cast<int*>(&m_dimensions.x), reinterpret_cast<int*>(&m_dimensions.y), reinterpret_cast<int*>(&m_channels));
		}
		~Image() = default;

		std::shared_ptr<const std::vector<byte>> read()
		{
			if (loaded()) return m_imageData.lock();

			stbi_set_flip_vertically_on_load(Config::IO::flipImages);

			const auto channels  = 4;
			const auto fileData  = File::read();
			const auto imageData = stbi_load_from_memory(fileData->data(), static_cast<int>(m_size), reinterpret_cast<int*>(&m_dimensions.x), reinterpret_cast<int*>(&m_dimensions.y), reinterpret_cast<int*>(&m_channels), channels);
			m_imageSize = (static_cast<size_t>(m_dimensions.x) * static_cast<size_t>(m_dimensions.y)) * channels;

			auto ptr = std::make_shared<const std::vector<byte>>(imageData, imageData + m_imageSize);
			m_imageData = ptr;

			stbi_image_free(imageData);

			return ptr;
		}
		Properties read_c(unsigned int channels, bool flip = false)
		{
            stbi_set_flip_vertically_on_load(flip);

			Vector2u dimensions{};
			size_t size{};

            const auto fileData = File::read();
            const auto imageData = stbi_load_from_memory(fileData->data(), static_cast<int>(fileData->size()), reinterpret_cast<int*>(&dimensions.x), reinterpret_cast<int*>(&dimensions.y), nullptr, channels);
            size = (static_cast<size_t>(dimensions.x) * static_cast<size_t>(dimensions.y)) * channels;

			const std::vector<byte> data{ imageData, imageData + size };
			auto result = Properties{ dimensions, size, channels, data };

            stbi_image_free(imageData);

			return result;
		}
		void write(std::span<const byte>& data) override
		{
			throw std::logic_error{ "Not implemented!" };
		}

		bool loaded() const override
		{
			return !m_imageData.expired();
		}

		Vector2u dimensions() const
		{
			return m_dimensions;
		}
		unsigned int channels() const
		{
			return m_channels;
		}

	private:
		Vector2u m_dimensions{};
		unsigned int m_channels{};

		std::weak_ptr<const std::vector<byte>> m_imageData{};
		size_t m_imageSize{};
	};
}
