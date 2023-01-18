#pragma once

#include "stdafx.hpp"

#include "Entry.hpp"

namespace hlx
{
	struct File : public Entry
	{
	public:
		explicit File(const std::filesystem::path& path)
			: Entry{ path }, m_size{ std::filesystem::file_size(m_path) } {}

		virtual const std::shared_ptr<std::vector<byte>> read()
		{
			if (!m_data.expired()) return m_data.lock();

			std::ifstream file(m_path, std::ios::binary);
			auto result = std::make_shared<std::vector<byte>>(std::istreambuf_iterator<char>{ file }, std::istreambuf_iterator<char>{});
			m_data = result;

			return result;
		}
		virtual void write(const std::vector<byte>& data)
		{
			throw std::logic_error{ "The method or operation has not been implemented!" };
		}

        size_t size() const
        {
            return m_size;
        }

    protected:
        std::weak_ptr<std::vector<byte>> m_data{};
		size_t m_size{};
	};
}
