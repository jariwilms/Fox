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
        using Access = api::Buffer::Access;

        explicit Buffer(std::span<const T> data)
            : m_size{ static_cast<gl::size_t>(data.size_bytes()) }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(
                m_handle, 
                glf::Buffer::StorageFlags::DynamicStorage | 
                glf::Buffer::StorageFlags::Read           | 
                glf::Buffer::StorageFlags::Write          | 
                glf::Buffer::StorageFlags::Persistent     | 
                glf::Buffer::StorageFlags::Coherent       , 
                data);
        }
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
                 Buffer(Buffer&&) noexcept = default;
                ~Buffer()
        {
            if (m_span) unmap();
            gl::delete_buffer(m_handle);
        }

        void copy      (                   std::span<const T> data)
        {
            gl::buffer_data(m_handle, gl::offset_t{ 0u }, data);
        }
        void copy_range(gl::index_t index, std::span<const T> data)
        {
            gl::buffer_data(m_handle, static_cast<gl::offset_t>(index * sizeof(T)), data);
        }

        auto map  (std::optional<gl::ByteRange> range = {})
        {
            if (!is_mapped() && range != m_range)
            {
                auto* ptr = gl::map_buffer<T>(
                                m_handle, 
                                glf::Buffer::Mapping::AccessFlags::ReadWrite     |
                                glf::Buffer::Mapping::AccessFlags::Persistent    |
                                glf::Buffer::Mapping::AccessFlags::Coherent      |
                                glf::Buffer::Mapping::AccessFlags::FlushExplicit ,
                                range);

                if   (range.has_value())
                {
                    m_span   = std::make_shared<std::span<T>>(ptr, range->size - range->offset);
                    m_range = range.value();
                }
                else
                {
                    m_span   = std::make_shared<std::span<T>>(ptr, count());
                    m_range = gl::ByteRange{ static_cast<gl::size_t>(m_span->size_bytes()) };
                }
            }

            return std::weak_ptr<std::span<T>>(m_span);
        }
        void flush(              gl::ByteRange  range     )
        {
            gl::flush_buffer_range(m_handle, range);
        }
        void unmap()
        {
            m_span.reset();
            gl::unmap_buffer(m_handle);
        }

        auto size     () const
        {
            return m_size;
        }
        auto count    () const
        {
            return static_cast<gl::count_t>(size() / sizeof(T));
        }
        auto is_mapped() const
        {
            return m_span.operator bool();
        }

        Buffer& operator=(Buffer&&) noexcept = default;

    private:
        std::shared_ptr<std::span<T>> m_span{};
        gl::ByteRange                 m_range{ gl::size_t{} };
        gl::size_t                    m_size{};
    };
    template<typename T>
    class UniformBuffer : public gl::Object
    {
    public:
        using Access = api::Buffer::Access;

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

        void bind_index(gl::index_t index) const
        {
            gl::bind_buffer_base(m_handle, glf::Buffer::BaseTarget::UniformBuffer, index);
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
        using Access = api::Buffer::Access;

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

        void bind_index(gl::index_t index, std::optional<gl::range_t> range = {}) const
        {
            if   (range.has_value()) gl::bind_buffer_range(m_handle, glf::Buffer::BaseTarget::UniformBuffer, index, gl::ByteRange{ static_cast<gl::size_t>(range->count * sizeof(T)), static_cast<gl::offset_t>(range->index * sizeof(T)) });
            else                     gl::bind_buffer_base (m_handle, glf::Buffer::BaseTarget::UniformBuffer, index                                                                                                                          );
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
