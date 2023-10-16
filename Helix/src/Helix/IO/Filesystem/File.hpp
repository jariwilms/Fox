#pragma once

#include "stdafx.hpp"

#include "Entry.hpp"

#include "Helix/Core/Library/Utility/Utility.hpp"
#include "Helix/Core/Library/Utility/Define.hpp"

namespace hlx
{
	class File : public Entry
	{
	public:
        explicit File(const std::filesystem::path& path)
            : Entry{ path }
        {
            m_stream.exceptions(std::fstream::badbit);
            m_stream.open(m_path, std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
        }
        virtual ~File() = default;

        static std::shared_ptr<File> touch(const std::filesystem::path& path)
        {
            std::fstream{ path, std::ios::out }.close();

            return std::make_shared<File>(path);
        }

        void save()
        {
            m_stream.flush();
        }

        std::shared_ptr<const std::vector<byte>> read(unsigned int count = 0u)
        {
            //The vector allocator default-initializes all data when resizing. This is redundant and costly on larger files, so a custom allocator is used
            auto buffer = std::make_unique<std::vector<byte>>();
            reinterpret_cast<std::vector<byte, utl::default_init_allocator<byte>>*>(buffer.get())->resize(count ? count : size());

            read_data(reinterpret_cast<char*>(buffer->data()), buffer->size());
            return buffer;
        }
        void write(std::span<const byte> data)
        {
            write_data(reinterpret_cast<const char*>(data.data()), data.size_bytes());
        }
        void write(std::string_view data)
        {
            write_data(data.data(), data.size());
        }

        void truncate()
        {
            m_stream.open(m_path, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
        }

        std::filesystem::path           extension()       const
        {
            return m_path.extension();
        }
        std::filesystem::file_time_type last_write_time() const
        {
            return std::filesystem::last_write_time(m_path);
        }
        size_t                          size()            const
        {
            return std::filesystem::file_size(m_path);
        }

	protected:
        void read_data(char* buffer, size_t size)
        {
            m_stream.read(buffer, size);
        }
        void write_data(const char* data, size_t size)
        {
            m_stream.write(data, size);
        }

        std::fstream m_stream{};
	};
}
