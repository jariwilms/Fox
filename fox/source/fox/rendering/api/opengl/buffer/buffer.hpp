#pragma once

#include <stdafx.hpp>

#include <fox/core/utility/utility.hpp>
#include <fox/rendering/api/opengl/opengl.hpp>
#include <fox/rendering/base/buffer/buffer.hpp>

namespace fox::gfx::api::gl
{
    template<typename T>
    class Buffer : public gl::Object
    {
    public:
        explicit Buffer(gl::count_t count)
            : size_{ static_cast<gl::size_t>(count * sizeof(T)) }
        {
            handle_ = gl::create_buffer();
            
            gl::buffer_storage(
                handle_,
                glf::Buffer::StorageFlags::DynamicStorage |
                glf::Buffer::StorageFlags::ReadWrite      |
                glf::Buffer::StorageFlags::Persistent     |
                glf::Buffer::StorageFlags::Coherent       ,
                size_);
        }
        explicit Buffer(std::span<const T> data)
            : size_{ static_cast<gl::size_t>(data.size_bytes()) }
        {
            handle_ = gl::create_buffer();
            
            gl::buffer_storage(
                handle_, 
                glf::Buffer::StorageFlags::DynamicStorage | 
                glf::Buffer::StorageFlags::ReadWrite      | 
                glf::Buffer::StorageFlags::Persistent     | 
                glf::Buffer::StorageFlags::Coherent       , 
                data);
        }
                 Buffer(Buffer&&) noexcept = default;
                ~Buffer()
        {
            if (is_mapped()) unmap();
            gl::delete_buffer(handle_);
        }

        void copy      (                   std::span<const T> data)
        {
            if (std::cmp_greater(data.size_bytes(), size())) throw std::invalid_argument{ "Data exceeds buffer size!" };

            gl::buffer_data(handle_, gl::offset_t{ 0u }, data);
        }
        void copy_range(gl::index_t index, std::span<const T> data)
        {
            if (std::cmp_greater_equal(index, count())) throw std::invalid_argument{ "Index out of range!" };

            gl::buffer_data(handle_, static_cast<gl::offset_t>(index * sizeof(T)), data);
        }

        auto map      ()
        {
            if (is_mapped()) unmap();

            auto* ptr = gl::map_buffer_range<T>(
                handle_, 
                glf::Buffer::Mapping::RangeAccessFlags::ReadWrite    |
                glf::Buffer::Mapping::RangeAccessFlags::Persistent   |
                glf::Buffer::Mapping::RangeAccessFlags::Coherent     ,
                gl::byterange_t{ size() });

            data_  = std::make_shared<std::span<T>>(ptr, count());
            range_ = count();

            return std::weak_ptr<std::span<T>>(data_);
        }
        auto map_range(gl::range_t range)
        {
            if (is_mapped()) unmap();

            range_.count = std::min(range->count, count()               );
            range_.index = std::min(range->index, count() - range->count);

            auto* ptr = gl::map_buffer_range<T>(
                handle_,
                glf::Buffer::Mapping::RangeAccessFlags::ReadWrite    |
                glf::Buffer::Mapping::RangeAccessFlags::Persistent   |
                glf::Buffer::Mapping::RangeAccessFlags::Coherent     |
                glf::Buffer::Mapping::RangeAccessFlags::FlushExplicit,
                gl::byterange_t{ static_cast<gl::size_t>(range_.count * sizeof(T)), static_cast<gl::offset_t>(range_.index * sizeof(T)) });

            data_ = std::make_shared<std::span<T>>(ptr, range_.count);
            
            return std::weak_ptr<std::span<T>>(data_);
        }
        auto is_mapped() const -> gl::bool_t
        {
            return data_.operator bool();
        }
        auto unmap    ()
        {
            data_.reset();
            locks_.clear();
            
            return gl::unmap_buffer(handle_);
        }

        void lock_range (gl::range_t range)
        {
            range.count = std::min(range->count, count()               );
            range.index = std::min(range->index, count() - range->count);

            locks_.emplace_back(range, gl::fence_sync());
        }
        void await_range(gl::range_t range)
        {
            std::vector<gl::lock_t> locks{};

            for (const auto& [lock, sync] : locks_)
            {
                if (std::max(range.index, lock.index) < std::min(range.index + range.count, lock.index + lock.count))
                {
                    auto command = glf::Synchronization::Command::None;
                    auto time    = gl::time_t{};

                    while (gl::True)
                    {
                        auto status = gl::client_wait_sync(sync, command, time);

                        if (status == glf::Synchronization::Status::AlreadySignaled   ) break;
                        if (status == glf::Synchronization::Status::ConditionSatisfied) break;
                        if (status == glf::Synchronization::Status::WaitFailed        ) throw std::runtime_error{ "An error occurred!" };

                        command = glf::Synchronization::Command::Flush;
                        time    = static_cast<gl::time_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds{ 1u }).count());
                    }

                    gl::delete_sync(sync);
                }
                else
                {
                    locks.emplace_back(lock, sync);
                }
            }

            locks_ = std::move(locks);
        }

        auto size () const
        {
            return size_;
        }
        auto count() const
        {
            return static_cast<gl::count_t>(size() / sizeof(T));
        }
        auto data ()
        {
            return std::weak_ptr<std::span<T>>{ data_ };
        }

        Buffer& operator=(Buffer&&) noexcept = default;

    private:
        gl::size_t                    size_{};
        gl::range_t                   range_{};
        std::vector<gl::lock_t>       locks_{};
        std::shared_ptr<std::span<T>> data_{};
    };
    template<typename T>
    class UniformBuffer : public gl::Object
    {
    public:
        explicit UniformBuffer(const T& data = {})
            : size_{ static_cast<gl::size_t>(sizeof(T)) }
        {
            handle_ = gl::create_buffer();

            gl::buffer_storage(handle_, glf::Buffer::StorageFlags::DynamicStorage, std::span<const T>{ &data, 1u });
        }
                 UniformBuffer(UniformBuffer&&) noexcept = default;
                ~UniformBuffer()
        {
            gl::delete_buffer(handle_);
        }

        void bind(gl::binding_t binding) const
        {
            gl::bind_buffer_base(handle_, glf::Buffer::BaseTarget::UniformBuffer, binding);
        }

        void copy    (const T& data)
        {
            gl::buffer_data(handle_, gl::offset_t{ 0u }, std::span<const T>{ &data, 1u });
        }
        template<typename... T>
        void copy_sub(gl::offset_t offset, const std::tuple<T...>& data)
        {
            std::array<gl::byte_t, (sizeof(T) + ... + 0u)> buffer{};

            if (std::cmp_greater(offset + buffer.size(), size())) throw std::invalid_argument{ "The given data is too large!" };

            std::apply([&buffer](auto&&... args)
                {
                    gl::offset_t offset{};
                    ((std::memcpy(buffer.data() + offset, &args, sizeof(args)), offset += sizeof(args)), ...);
                }, data);

            gl::buffer_data(handle_, offset, fox::as_bytes(buffer));
        }

        auto size() const
        {
            return size_;
        }

        UniformBuffer& operator=(UniformBuffer&&) noexcept = default;

    private:
        gl::size_t size_{};
    };
    template<typename T, gl::count_t N>
    class UniformArrayBuffer : public gl::Object
    {
    public:
        explicit UniformArrayBuffer()
            : size_{ static_cast<gl::size_t>(N * sizeof(T)) }
        {
            handle_ = gl::create_buffer();

            gl::buffer_storage(
                handle_, 
                glf::Buffer::StorageFlags::DynamicStorage | 
                glf::Buffer::StorageFlags::ReadWrite      | 
                glf::Buffer::StorageFlags::Persistent     | 
                glf::Buffer::StorageFlags::Coherent       , 
                gl::size_t{ N * sizeof(T) });
        }
        explicit UniformArrayBuffer(std::span<const T> data)
            : size_{ static_cast<gl::size_t>(data.size_bytes()) }
        {
            handle_ = gl::create_buffer();

            gl::buffer_storage(
                handle_, 
                glf::Buffer::StorageFlags::DynamicStorage | 
                glf::Buffer::StorageFlags::ReadWrite      | 
                glf::Buffer::StorageFlags::Persistent     | 
                glf::Buffer::StorageFlags::Coherent       , 
                data);
        }
                 UniformArrayBuffer(UniformArrayBuffer&&) noexcept = default;
                ~UniformArrayBuffer()
        {
            gl::delete_buffer(handle_);
        }

        void bind      (gl::binding_t binding) const
        {
            gl::bind_buffer_base (handle_, glf::Buffer::BaseTarget::UniformBuffer, binding                                                                                                                           );
        }
        void bind_range(gl::binding_t binding, gl::range_t range) const
        {
            gl::bind_buffer_range(
                handle_, glf::Buffer::BaseTarget::UniformBuffer, binding, 
                gl::byterange_t{ static_cast<gl::size_t>(range.count * sizeof(T)), static_cast<gl::offset_t>(range.index * sizeof(T)) });
        }

        void copy      (std::span<const T, N> data)
        {
            gl::buffer_data(handle_, gl::offset_t{ 0u }, std::span<const T>{ data.data(), data.size() });
        }
        void copy_index(fox::index_t index, const T& data)
        {
            gl::buffer_data(handle_, index * sizeof(T), std::span<const T>{ &data, 1u });
        }
        void copy_range(fox::index_t index, std::span<const T> data)
        {
            gl::buffer_data(handle_, index * sizeof(T), data);
        }

        auto map      ()
        {
            if (is_mapped()) unmap();

            auto* ptr = gl::map_buffer_range<T>(
                handle_, 
                glf::Buffer::Mapping::RangeAccessFlags::ReadWrite    |
                glf::Buffer::Mapping::RangeAccessFlags::Persistent   |
                glf::Buffer::Mapping::RangeAccessFlags::Coherent     ,
                gl::byterange_t{ size() });

            data_  = std::make_shared<std::span<T>>(ptr, count());
            range_ = count();

            return std::weak_ptr<std::span<T>>(data_);
        }
        auto map_range(gl::range_t range)
        {
            if (is_mapped()) unmap();

            range_.count = std::min(range->count, count()               );
            range_.index = std::min(range->index, count() - range->count);

            auto* ptr = gl::map_buffer_range<T>(
                handle_,
                glf::Buffer::Mapping::RangeAccessFlags::ReadWrite    |
                glf::Buffer::Mapping::RangeAccessFlags::Persistent   |
                glf::Buffer::Mapping::RangeAccessFlags::Coherent     |
                glf::Buffer::Mapping::RangeAccessFlags::FlushExplicit,
                gl::byterange_t{ static_cast<gl::size_t>(range_.count * sizeof(T)), static_cast<gl::offset_t>(range_.index * sizeof(T)) });

            data_ = std::make_shared<std::span<T>>(ptr, range_.count);
            
            return std::weak_ptr<std::span<T>>(data_);
        }
        auto is_mapped() const
        {
            return static_cast<gl::bool_t>(data_.operator bool());
        }
        auto unmap    ()
        {
            data_.reset();
            locks_.clear();
            
            return gl::unmap_buffer(handle_);
        }

        void lock_range (gl::range_t range)
        {
            range.count = std::min(range->count, count()               );
            range.index = std::min(range->index, count() - range->count);

            locks_.emplace_back(range, gl::fence_sync());
        }
        void await_range(gl::range_t range)
        {
            const auto& range_overlaps = [](gl::range_t first, gl::range_t second)
                {
                    return std::cmp_less(first.index, second.index + second.count) and std::cmp_less(second.index, first.index + first.count);
                };



            std::vector<gl::lock_t> locks{};

            for (const auto& [lock, sync] : locks_)
            {
                if (range_overlaps(range, lock))
                {
                    auto command = glf::Synchronization::Command::None;
                    auto time    = gl::time_t{};

                    while (gl::True)
                    {
                        const auto& status = gl::client_wait_sync(sync, command, time);

                        if (status == glf::Synchronization::Status::AlreadySignaled   ) break;
                        if (status == glf::Synchronization::Status::ConditionSatisfied) break;
                        if (status == glf::Synchronization::Status::WaitFailed        ) throw std::runtime_error{ "An error occurred!" };

                        command = glf::Synchronization::Command::Flush;
                        time    = static_cast<gl::time_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds{ 1u }).count());
                    }

                    gl::delete_sync(sync);
                }
                else
                {
                    locks.emplace_back(lock, sync);
                }
            }

            locks_ = std::move(locks);
        }

        auto size () const
        {
            return size_;
        }
        auto count() const
        {
            return N;
        }

        UniformArrayBuffer& operator=(UniformArrayBuffer&&) noexcept = default;

    private:
        gl::size_t                    size_{};
        gl::range_t                   range_{};
        std::vector<gl::lock_t>       locks_{};
        std::shared_ptr<std::span<T>> data_{};
    };
}
