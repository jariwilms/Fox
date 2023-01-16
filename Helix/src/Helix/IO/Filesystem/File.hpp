#pragma once

#include "stdafx.hpp"

#include "Entry.hpp"

namespace hlx
{
	struct File : public Entry
	{
	public:
		explicit File(const std::filesystem::path& path)
			: Entry{ path }
		{
            const auto exists = std::filesystem::exists(path);
            if (!exists) throw std::invalid_argument{ "The given path does not exist!" };

			const auto isDirectory = std::filesystem::is_directory(path);
			if (isDirectory) throw std::invalid_argument{ "The given path leads to a directory!" };

			m_size = std::filesystem::file_size(m_path);
		}

		virtual std::shared_ptr<std::vector<byte>> read()                      //TODO: keep data in memory or always read?
		{
			if (!m_data.expired()) return m_data.lock();

			std::ifstream file(m_path, std::ios::binary);
			std::vector<byte> buffer{ std::istreambuf_iterator<char>{ file }, std::istreambuf_iterator<char>{} };
			buffer.push_back(0);

			return std::make_shared<std::vector<byte>>(std::move(buffer));
		}
		virtual void write(const std::vector<byte>& data)
		{
			throw std::logic_error{ "The method or operation has not been implemented!" };
		}

	protected:
		std::weak_ptr<std::vector<byte>> m_data{};
	};
}
