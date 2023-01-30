#pragma once

#include "stdafx.hpp"

#include "stb/stb_image.h"

#include "File.hpp"

namespace hlx
{
	struct Image : public File
	{
	public:
		explicit Image(const std::filesystem::path& path)
			: File{ path }
		{

		}

		const std::shared_ptr<std::vector<byte>> read(bool flip = false)
		{
			if (!m_imageData.expired()) return m_imageData.lock();

			stbi_set_flip_vertically_on_load(flip);

			const auto channels = 4;
			const auto image    = File::read();
			const auto rawImage = stbi_load_from_memory(image->data(), static_cast<int>(m_size), reinterpret_cast<int*>(&m_dimensions.x), reinterpret_cast<int*>(&m_dimensions.y), reinterpret_cast<int*>(&m_channels), channels);
			m_rawSize = (static_cast<size_t>(m_dimensions.x) * static_cast<size_t>(m_dimensions.y)) * channels;

			auto result = std::make_shared<std::vector<byte>>(rawImage, rawImage + m_rawSize);
			m_imageData = result;
			stbi_image_free(rawImage);

			return result;
		}
		void write(const std::vector<byte>& data) override
		{
			throw std::logic_error{ "Not implemented!" };
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

		std::weak_ptr<std::vector<byte>> m_imageData;
		size_t m_rawSize{};
	};
}
