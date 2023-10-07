#pragma once

#include "stdafx.hpp"

#pragma warning(push)
#pragma warning(disable: 6262 26827 26819 26451)
#include <stb_image.h>
#pragma warning(pop)

#include "File.hpp"

namespace hlx
{
	class Image : protected File
	{
	public:
		explicit Image(const std::filesystem::path& path)
			: File{ path }
		{
			update_meta_data();
		}
		virtual ~Image() = default;

		std::unique_ptr<const std::vector<byte>> read(unsigned int components = 0u)
		{
			stbi_set_flip_vertically_on_load(Config::IO::flipImages);

			if (components == 0) components = m_channels;
			else                 components = std::min(components, 4u);

			int x{}, y{}, c{};
			const auto& str     = m_path.string();
			const auto& rawSize = static_cast<size_t>(m_dimensions.x * m_dimensions.y * components);
			auto* image         = reinterpret_cast<byte*>(stbi_load(str.c_str(), &x, &y, &c, components));

            auto buffer = std::make_unique<const std::vector<byte>>(image, image + rawSize);
			stbi_image_free(image);

			return buffer;
		}
		void write(std::span<const byte> data)
		{
			throw std::logic_error{ "The method or operation has not been implemented!" };
		}

		const Vector2u& dimensions() const
		{
			return m_dimensions;
		}
		unsigned int    channels()   const
		{
			return m_channels;
		}

	protected:
		virtual void update_meta_data() override
		{
            int x{}, y{}, c{};
            const auto& str     = m_path.string();
            const auto& success = stbi_info(str.c_str(), &x, &y, &c);

            if (!success) throw std::runtime_error{ std::format("Image info could not be retrieved! reason: {}", stbi_failure_reason()) };

            m_dimensions = { x, y };
            m_channels = c;
		}

		Vector2u     m_dimensions{};
		unsigned int m_channels{};
	};
}
