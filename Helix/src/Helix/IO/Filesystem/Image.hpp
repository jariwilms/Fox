#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"
#include "stb/stb_image.h"

#include "File.hpp"

namespace hlx
{
	struct Image : public File
	{
	public:
		using File::File;

		std::shared_ptr<std::vector<byte>> read() override
		{
			const auto buffer = File::read();
			const auto image = stbi_load_from_memory(buffer->data(), static_cast<int>(m_size), reinterpret_cast<int*>(&m_dimensions.x), reinterpret_cast<int*>(&m_dimensions.y), reinterpret_cast<int*>(&m_channels), 0);
			m_rawSize = (static_cast<size_t>(m_dimensions.x) * static_cast<size_t>(m_dimensions.y));

			auto result = std::make_shared<std::vector<byte>>(image, image + m_size);
			stbi_image_free(image);

			return result;
		}
		void write(const std::vector<byte>& data) override                     //Make File::write() protected? => using File::write; in classes that need it
		{

		}

		glm::uvec2 dimensions() const
		{
			return m_dimensions;
		}
		unsigned int channels() const
		{
			return m_channels;
		}

	private:
		glm::uvec2 m_dimensions{};
		unsigned int m_channels;

		std::weak_ptr<std::vector<byte>> m_imageData;
		size_t m_rawSize{};
	};
}
