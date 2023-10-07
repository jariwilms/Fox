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
            : Entry{ path }, m_extension{ m_path.extension() }
        {
            m_stream.exceptions(std::fstream::badbit);
            update_meta_data();
        }
        virtual ~File() = default;

        static std::shared_ptr<File> touch(const std::filesystem::path& path)
        {
            std::fstream{ path, std::ios::out };

            return std::make_shared<File>(path);
        }

        std::unique_ptr<const std::vector<byte>> read()
        {
            //The vector allocator default-initializes all data when resizing. This is redundant and costly on larger files, so a custom allocator is used
            auto buffer = std::make_unique<std::vector<byte>>();
            reinterpret_cast<std::vector<byte, utl::default_init_allocator<byte>>*>(buffer.get())->resize(size());

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
            m_stream.open(m_path, std::ios::out | std::ios::trunc);
            m_stream.close();
        }

        const std::filesystem::path&           extension()       const
        {
            return m_extension;
        }
        const std::filesystem::file_time_type& last_write_time() const
        {
            return m_lastWriteTime;
        }
        size_t                                 size()            const
        {
            return m_size;
        }

	protected:
        void read_data(char* buffer, size_t size)
        {
            m_stream.open(m_path, std::ios::in | std::ios::binary);
            m_stream.read(buffer, size);
            m_stream.close();
        }
        void write_data(const char* data, size_t size)
        {
            m_stream.open(m_path, std::ios::out | std::ios::app | std::ios::binary);
            m_stream.write(data, size);
            m_stream.close();
        }

        virtual void update_meta_data()
        {
            m_lastWriteTime = std::filesystem::last_write_time(m_path);
            m_size          = std::filesystem::file_size(m_path);
        }

        std::fstream m_stream{};

        std::filesystem::path           m_extension{};
        std::filesystem::file_time_type m_lastWriteTime{};
        size_t                          m_size{};
	};
}
