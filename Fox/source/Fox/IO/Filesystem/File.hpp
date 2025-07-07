#pragma once

#include <stdafx.hpp>

#include <fox/core/memory/adapter/no_init_adapter.hpp>
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
            stream_.exceptions(std::fstream::badbit);
            stream_.open      (path_, std::ios::in | std::ios::out | std::ios::app | std::ios::binary);

            if (!stream_) throw std::runtime_error{ "Failed to open file!" };
        }

        static auto touch(const std::filesystem::path& path) -> std::shared_ptr<io::File>
        {
            std::ofstream{ path }.close();
            
            return std::make_shared<io::File>(path);
        }

        auto read (std::optional<fox::size_t> limit = {}) -> std::shared_ptr<std::vector<fox::byte_t>>
        {
            const auto bufferSize = std::min(limit.value_or(size()), size());
                  auto buffer     = std::vector<fox::byte_t, memory::no_init_adapter<std::allocator<fox::byte_t>>>(bufferSize);
                  
            read_data(buffer.data(), buffer.size());
            
            return std::make_shared<std::vector<fox::byte_t>>(std::from_range, std::move(buffer));
        }
        void write(std::span<const fox::byte_t> data)
        {
            write_data(data.data(), data.size_bytes());
        }

        void save    ()
        {
            stream_.flush();
        }
        void resize  (fox::size_t size)
        {
            std::filesystem::resize_file(path_, size);
        }
        void truncate()
        {
            stream_.open(path_, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
        }
        void rename  (const std::string& name)
        {
            auto parent  = path_.parent_path();
            auto newPath = parent / name;

            std::filesystem::rename(path_, newPath);

            path_ = newPath;
            name_ = name;
        }

        auto extension      () const -> std::filesystem::path
        {
            return path_.extension();
        }
        auto last_write_time() const -> std::filesystem::file_time_type
        {
            return std::filesystem::last_write_time(path_);
        }
        auto size           () const -> fox::size_t
        {
            return std::filesystem::file_size(path_);
        }

	protected:
        void read_data (fox::byte_t      * data, fox::size_t size)
        {
            stream_.read(std::bit_cast<fox::char_t*>(data), size);
        }
        void write_data(fox::byte_t const* data, fox::size_t size)
        {
            stream_.write(std::bit_cast<const fox::char_t*>(data), size);
        }

        std::fstream stream_{};
	};
}
