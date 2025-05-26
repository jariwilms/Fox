#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/API/Buffer/Buffer.hpp"

namespace fox::gfx::api::gl
{
    template<typename T>
    class Buffer : public gl::Object
    {
    public:
        using lock_t = std::tuple<gl::range_t, gl::sync_t>;

        explicit Buffer(gl::count_t count)
            : m_size{ static_cast<gl::size_t>(count * sizeof(T)) }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(
                m_handle,
                glf::Buffer::StorageFlags::DynamicStorage |
                glf::Buffer::StorageFlags::ReadWrite      |
                glf::Buffer::StorageFlags::Persistent     |
                glf::Buffer::StorageFlags::Coherent       ,
                m_size);
        }
        explicit Buffer(std::span<const T> data)
            : m_size{ static_cast<gl::size_t>(data.size_bytes()) }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(
                m_handle, 
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
            gl::delete_buffer(m_handle);
        }

        void copy      (                   std::span<const T> data)
        {
            if (data.size_bytes() > size()) throw std::invalid_argument{ "Data exceeds buffer size!" };
            gl::buffer_data(m_handle, gl::offset_t{ 0u }, data);
        }
        void copy_range(gl::index_t index, std::span<const T> data)
        {
            if (index >= count()) throw std::invalid_argument{ "Index out of range!" };
            gl::buffer_data(m_handle, static_cast<gl::offset_t>(index * sizeof(T)), data);
        }

        auto map      ()
        {
            if (is_mapped()) unmap();

            auto* ptr = gl::map_buffer_range<T>(
                m_handle, 
                glf::Buffer::Mapping::RangeAccessFlags::ReadWrite    |
                glf::Buffer::Mapping::RangeAccessFlags::Persistent   |
                glf::Buffer::Mapping::RangeAccessFlags::Coherent     ,
                gl::byterange_t{ size() });

            m_data  = std::make_shared<std::span<T>>(ptr, count());
            m_range = count();

            return std::weak_ptr<std::span<T>>(m_data);
        }
        auto map_range(gl::range_t range)
        {
            if (is_mapped()) unmap();

            m_range.count = std::min(range->count, count()               );
            m_range.index = std::min(range->index, count() - range->count);

            auto* ptr = gl::map_buffer_range<T>(
                m_handle,
                glf::Buffer::Mapping::RangeAccessFlags::ReadWrite    |
                glf::Buffer::Mapping::RangeAccessFlags::Persistent   |
                glf::Buffer::Mapping::RangeAccessFlags::Coherent     |
                glf::Buffer::Mapping::RangeAccessFlags::FlushExplicit,
                gl::byterange_t{ static_cast<gl::size_t>(m_range.count * sizeof(T)), static_cast<gl::offset_t>(m_range.index * sizeof(T)) });

            m_data = std::make_shared<std::span<T>>(ptr, m_range.count);
            
            return std::weak_ptr<std::span<T>>(m_data);
        }
        auto is_mapped() const
        {
            return m_data.operator bool();
        }
        void unmap    ()
        {
            m_data.reset();
            m_locks.clear();
            gl::unmap_buffer(m_handle);
        }

        void lock (gl::range_t range)
        {
            range.count = std::min(range->count, count()               );
            range.index = std::min(range->index, count() - range->count);

            m_locks.emplace_back(range, gl::fence_sync());
        }
        void await(gl::range_t range)
        {
            const auto& range_overlaps = [](gl::range_t first, gl::range_t second)
                {
                    return (first.index < second.index + second.count) and (second.index < first.index + first.count);
                };



            std::vector<lock_t> locks{};

            for (const auto& [lock, sync] : m_locks)
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

            m_locks = std::move(locks);
        }

        auto size () const
        {
            return m_size;
        }
        auto count() const
        {
            return static_cast<gl::count_t>(size() / sizeof(T));
        }
        auto data ()
        {
            return std::weak_ptr<std::span<T>>{ m_data };
        }

        Buffer& operator=(Buffer&&) noexcept = default;

    private:
        gl::size_t                    m_size{};
        gl::range_t                   m_range{};
        std::vector<lock_t>           m_locks{};
        std::shared_ptr<std::span<T>> m_data{};
    };
    template<typename T>
    class UniformBuffer : public gl::Object
    {
    public:
        explicit UniformBuffer(const T& data = {})
            : m_size{ static_cast<gl::size_t>(sizeof(T)) }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(m_handle, glf::Buffer::StorageFlags::DynamicStorage, std::span<const T>{ &data, 1u });
        }
                 UniformBuffer(UniformBuffer&&) noexcept = default;
                ~UniformBuffer()
        {
            gl::delete_buffer(m_handle);
        }

        void bind(gl::binding_t binding) const
        {
            gl::bind_buffer_base(m_handle, glf::Buffer::BaseTarget::UniformBuffer, binding);
        }

        void copy    (const T& data)
        {
            gl::buffer_data(m_handle, 0, std::span<const T>{ &data, 1u });
        }
        template<typename... T>
        void copy_sub(gl::offset_t offset, const std::tuple<T...>& data) //TODO: check if used with std::tie instead of std::make_tuple?
        {
            //This method lets you copy a tuple of any amount of types into an allocated buffer
            //There is no guarantee that a parameter pack will be evaluated in order of declaration, so it can not be used
            //Arguments in a braced initializer list eg. tuple{ myval1, myval2 }, are required to be evaluated first to last
            //This guarantees that the data will be copied into the uniform buffer in order

            std::array<gl::byte_t, (sizeof(T) + ... + 0u)> buffer{};

            std::apply([&buffer](auto&&... args)
                {
                    gl::size_t size{};
                    ((std::memcpy(buffer.data() + size, &args, sizeof(args)), size += sizeof(args)), ...);
                }, data);

            gl::buffer_data(m_handle, offset, std::span<const gl::byte_t>{ buffer.data(), buffer.size() });
        }

        auto size() const
        {
            return m_size;
        }

        UniformBuffer& operator=(UniformBuffer&&) noexcept = default;

    private:
        gl::size_t m_size{};
    };
    template<typename T, fox::uint32_t N>
    class UniformArrayBuffer : public gl::Object
    {
    public:
        explicit UniformArrayBuffer()
            : m_size{ static_cast<gl::size_t>(N * sizeof(T)) }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(m_handle, glf::Buffer::StorageFlags::DynamicStorage, gl::size_t{ N * sizeof(T) });
        }
        explicit UniformArrayBuffer(std::span<const T> data)
            : m_size{ static_cast<gl::size_t>(data.size_bytes()) }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(m_handle, glf::Buffer::StorageFlags::DynamicStorage, data);
        }
                 UniformArrayBuffer(UniformArrayBuffer&&) noexcept = default;
                ~UniformArrayBuffer()
        {
            gl::delete_buffer(m_handle);
        }

        void bind(gl::binding_t binding, std::optional<gl::range_t> range = {}) const
        {
            if   (range.has_value()) gl::bind_buffer_range(m_handle, glf::Buffer::BaseTarget::UniformBuffer, binding, gl::byterange_t{ static_cast<gl::size_t>(range->count * sizeof(T)), static_cast<gl::offset_t>(range->index * sizeof(T)) });
            else                     gl::bind_buffer_base (m_handle, glf::Buffer::BaseTarget::UniformBuffer, binding                                                                                                                           );
        }

        void copy      (std::span<const T, N> data)
        {
            gl::buffer_data(m_handle, gl::offset_t{ 0u }, std::span<const T>{ data.data(), data.size() });
        }
        void copy_index(fox::uint32_t index, const T& data)
        {
            gl::buffer_data(m_handle, index * sizeof(T), std::span<const T>{ &data, 1u });
        }
        void copy_range(fox::uint32_t index, std::span<const T> data)
        {
            gl::buffer_data(m_handle, index * sizeof(T), data);
        }

        auto size() const
        {
            return m_size;
        }

        UniformArrayBuffer& operator=(UniformArrayBuffer&&) noexcept = default;

    private:
        gl::size_t m_size{};
    };
}
