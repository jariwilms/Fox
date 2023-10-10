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
		enum class Format
		{
			GIF, 
			JPEG, 
			JPG, 
			PNG, 
			WEBP, 
		};

		Image() = default;
		explicit Image(std::span<const byte> data)
			: m_data{ data.begin(), data.end() }
		{
            int x{}, y{}, c{};
            const auto& success = stbi_info_from_memory(m_data.data(), static_cast<int>(data.size_bytes()), & x, &y, &c);
            if (!success) throw std::runtime_error{ std::format("Image info could not be retrieved! reason: {}", stbi_failure_reason()) };

            m_dimensions = { x, y };
            m_channels = c;
		}
		explicit Image(std::shared_ptr<File> file)
			: Image{ utl::to_span(*file->read()) } {}
		explicit Image(const Image& other) = delete;
		virtual ~Image() = default;

		std::unique_ptr<const std::vector<byte>> read(unsigned int components = 0u)
		{
            stbi_set_flip_vertically_on_load(Config::IO::flipImages);

            if (components == 0) components = m_channels;
            else                 components = std::min(components, 4u);

            int x{}, y{}, c{};
            const auto& len = static_cast<int>(m_dimensions.x * m_dimensions.y * components);
            auto* image = reinterpret_cast<byte*>(stbi_load_from_memory(m_data.data(), len, &x, &y, &c, components));

            auto buffer = std::make_unique<const std::vector<byte>>(image, image + len);
            stbi_image_free(image);

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

		Image& operator=(const Image&) = delete;

	private:
		std::vector<byte> m_data{};

		Vector2u     m_dimensions{};
		unsigned int m_channels{};
	};

	class Image2
	{
	public:
		Image2() = default;


	private:
		Vector2u     m_dimensions{};
		unsigned int m_channels{};
	};


}
