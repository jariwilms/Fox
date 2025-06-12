#pragma once

#include <stdafx.hpp>

#include <fox/core/memory/allocator/no_init.hpp>
#include <fox/core/utility/utility.hpp>
#include <fox/io/filesystem/entry.hpp>

namespace fox::io
{
	class File : public Entry
	{
	public:
        File(const std::filesystem::path& path)
            : Entry{ path }
        {
            m_stream.exceptions(std::fstream::badbit);
            m_stream.open      (m_path, std::ios::in | std::ios::out | std::ios::app | std::ios::binary);

            if (!m_stream) throw std::runtime_error{ "Failed to open file!" };
        }

        static auto touch(const std::filesystem::path& path) -> std::shared_ptr<io::File>
        {
            std::ofstream{ path }.close();
            
            return std::make_shared<io::File>(path);
        }

        auto read (std::optional<fox::size_t> limit = {}) -> std::shared_ptr<const std::vector<fox::byte_t>>
        {
            //The default vector allocator initializes all data when resizing.
            //This is redundant because we want the vector to take ownership of existing data.

            auto       buffer     = std::make_shared<std::vector<fox::byte_t>>();
            auto const bufferSize = std::min(limit.value_or(size()), size());

            reinterpret_cast<std::vector<fox::byte_t, memory::no_init_allocator<fox::byte_t>>*>(buffer.get())->resize(bufferSize);
            read_data(buffer->data(), buffer->size());

            return buffer;
        }
        void write(std::span<const fox::byte_t> data)
        {
            write_data(data.data(), data.size_bytes());
        }

        void save    ()
        {
            m_stream.flush();
        }
        void resize  (fox::size_t size)
        {
            std::filesystem::resize_file(m_path, size);
        }
        void truncate()
        {
            m_stream.open(m_path, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
        }
        void rename  (const std::string& name)
        {
            auto parent  = m_path.parent_path();
            auto newPath = parent / name;

            std::filesystem::rename(m_path, newPath);

            m_path = newPath;
            m_name = name;
        }

        auto extension      () const -> std::filesystem::path
        {
            return m_path.extension();
        }
        auto last_write_time() const -> std::filesystem::file_time_type
        {
            return std::filesystem::last_write_time(m_path);
        }
        auto size           () const -> fox::size_t
        {
            return std::filesystem::file_size(m_path);
        }

	protected:
        void read_data (fox::byte_t      * data, fox::size_t size)
        {
            m_stream.read(reinterpret_cast<fox::char_t*>(data), size);
        }
        void write_data(fox::byte_t const* data, fox::size_t size)
        {
            m_stream.write(reinterpret_cast<const fox::char_t*>(data), size);
        }

        std::fstream m_stream{};
	};
}
