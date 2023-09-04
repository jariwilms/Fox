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
            if (!std::filesystem::is_regular_file(path)) throw std::invalid_argument{ "The given path does not reference a file!" };

			m_extension = m_path.extension().string();
			m_lastWriteTime = std::filesystem::last_write_time(m_path);
			m_size = std::filesystem::file_size(m_path);
		}

		virtual std::shared_ptr<const std::vector<byte>> read()
		{
			if (loaded()) return m_data.lock();

			//TODO: custom input buffer size?
			std::ifstream input{ m_path, std::ios::binary };
			auto ptr = std::make_shared<const std::vector<byte>>(std::istreambuf_iterator<char>{ input }, std::istreambuf_iterator<char>{});
			m_data = ptr;

			return ptr;
		}
		virtual void write(std::span<const byte>& data)
		{
			std::ofstream output{ m_path };
			std::ostream_iterator<byte> outputIterator{ output };
			std::copy(data.begin(), data.end(), outputIterator);

            m_lastWriteTime = std::filesystem::last_write_time(m_path);
		}

		virtual bool loaded() const
		{
			return !m_data.expired();
		}

		const std::filesystem::path& extension() const
		{
			return m_extension;
		}
		const std::filesystem::file_time_type& last_write_time() const
		{
			return m_lastWriteTime;
		}
        size_t size() const
        {
            return m_size;
        }

    protected:
		std::filesystem::path m_extension{};
		std::filesystem::file_time_type m_lastWriteTime{};
		size_t m_size{};

		std::weak_ptr<const std::vector<byte>> m_data{};
	};
}
