#pragma once

#include "stdafx.hpp"

#include "Entry.hpp"

#include "Fox/Core/Library/Utility/Utility.hpp"

namespace fox::io
{
	class File : public Entry
	{
	public:
        explicit File(const std::filesystem::path& path)
            : Entry{ path }
        {
            m_stream.exceptions(std::fstream::badbit);
            m_stream.open(m_path, std::ios::in | std::ios::out | std::ios::app | std::ios::binary);

            if (!m_stream) throw std::runtime_error{ "Failed to open file!" };
        }
        virtual ~File() = default;

        static std::shared_ptr<File> touch(const std::filesystem::path& path)
        {
            std::fstream{ path, std::ios::out }.close();

            return std::make_shared<File>(path);
        }

        std::unique_ptr<const std::vector<fox::byte_t>> read(std::optional<fox::size_t> limit = {})
        {
            //The default vector allocator initializes all data when resizing.
            //This is redundant because we want the vector to take ownership of existing data.
                  auto buffer  = std::make_unique<std::vector<fox::byte_t>>();
            const auto maxSize = std::min(limit.value_or(size()), size());

            using vec_t = std::vector<fox::byte_t, utl::no_init_allocator<fox::byte_t>>;

            reinterpret_cast<vec_t*>(buffer.get())->resize(maxSize);
            read_data(reinterpret_cast<fox::char_t*>(buffer->data()), buffer->size());

            return buffer;
        }
        void                                            write(std::span<const fox::byte_t> data)
        {
            write_data(reinterpret_cast<const char*>(data.data()), data.size_bytes());
        }
        void                                            write(std::string_view data)
        {
            write_data(data.data(), data.size());
        }

        void save()
        {
            m_stream.flush();
        }
        void resize(fox::size_t size)
        {
            std::filesystem::resize_file(m_path, size);
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
        fox::size_t                     size()            const
        {
            return std::filesystem::file_size(m_path);
        }

	protected:
        void read_data(fox::char_t* buffer, fox::size_t size)
        {
            m_stream.read(buffer, size);
        }
        void write_data(const fox::char_t* data, fox::size_t size)
        {
            m_stream.write(data, size);
        }

        std::fstream m_stream{};
	};
}
