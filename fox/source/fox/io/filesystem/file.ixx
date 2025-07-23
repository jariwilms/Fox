export module fox.io.filesystem.file;

import std;
import fox.core.memory.adapter.no_init;
import fox.core.types;
import fox.core.utility;
import fox.io.filesystem.entry;

export namespace fox::io
{
    class file : public io::entry
    {
    public:
        explicit file(const std::filesystem::path& path)
            : io::entry{ path }
        {
            stream_.exceptions(std::fstream::badbit);
            stream_.open      (io::entry::path(), std::ios::in | std::ios::out | std::ios::app | std::ios::binary);

            if (!stream_) throw std::runtime_error{ "Failed to open file!" };
        }

        static auto touch   (const std::filesystem::path& path) -> std::shared_ptr<io::file>
        {
            return std::ofstream{ path }.close(), std::make_shared<io::file>(path);
        }

        auto read           (std::optional<fox::size_t> limit = std::nullopt) -> std::shared_ptr<std::vector<fox::byte_t>>
        {
            auto buffer = std::vector<fox::byte_t, memory::adapter::no_init<std::allocator<fox::byte_t>>>(limit.value_or(size()));
            read_data(buffer.data(), buffer.size());
            
            return std::make_shared<std::vector<fox::byte_t>>(std::from_range, std::move(buffer));
        }
        void write          (std::span<const fox::byte_t> data)
        {
            write_data(data.data(), data.size_bytes());
        }

        void save           ()
        {
            stream_.flush();
        }
        void resize         (fox::size_t size)
        {
            std::filesystem::resize_file(path(), size);
        }
        void truncate       ()
        {
            stream_.open(path(), std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
        }

        auto last_write_time() const -> std::filesystem::file_time_type
        {
            return std::filesystem::last_write_time(path());
        }
        auto size           () const -> fox::size_t
        {
            return std::filesystem::file_size(path());
        }

    private:
        void read_data (fox::byte_t      * data, fox::size_t size)
        {
            stream_.read(std::bit_cast<fox::char_t*>(data), std::min(size, io::file::size()));
        }
        void write_data(fox::byte_t const* data, fox::size_t size)
        {
            stream_.write(std::bit_cast<const fox::char_t*>(data), std::min(size, io::file::size()));
        }

        std::fstream stream_;
    };
}
