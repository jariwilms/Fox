#pragma once

#include "stdafx.hpp"

#include <stb_image.h>

#include "File.hpp"

namespace hlx
{
	struct Image : public File
	{
	public:
		explicit Image(const std::filesystem::path& path)
			: File{ path } {}
		~Image() = default;

		std::shared_ptr<const std::vector<byte>> read()
		{
			if (!m_imageData.expired()) return m_imageData.lock();

			stbi_set_flip_vertically_on_load(Config::IO::flipImages);

			const auto channels  = 4;
			const auto fileData  = File::read();
			const auto imageData = stbi_load_from_memory(fileData->data(), static_cast<int>(m_size), reinterpret_cast<int*>(&m_dimensions.x), reinterpret_cast<int*>(&m_dimensions.y), reinterpret_cast<int*>(&m_channels), channels);
			m_imageSize = (static_cast<size_t>(m_dimensions.x) * static_cast<size_t>(m_dimensions.y)) * channels;

			//std::shared_ptr<std::span<byte>> ptr{ new std::span<byte>{ imageData, imageData + m_imageSize }, [](std::span<byte>* ptr) { stbi_image_free(ptr->data()); delete[] ptr; } };
			auto ptr = std::make_shared<std::vector<byte>>(imageData, imageData + m_imageSize);
			m_imageData = ptr;

			stbi_image_free(imageData);

			return ptr;
		}
		void write(const std::span<byte>& data) override
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

		std::weak_ptr<std::vector<byte>> m_imageData{};
		size_t m_imageSize{};
	};
}
