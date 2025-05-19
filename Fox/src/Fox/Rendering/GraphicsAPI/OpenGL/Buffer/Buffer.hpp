#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/API/Buffer/Buffer.hpp"

namespace fox::gfx::api::gl
{
    class BufferObject : public gl::Object
    {
    public:
        using Access = api::Buffer::Access;
        using Type   = api::Buffer::Type;

        gl::size_t size() const
        {
            return m_size;
        }

    protected:
        BufferObject(gl::size_t size)
            : m_size{ size } {}

        gl::size_t m_size{};
    };



    template<typename T>
    class Buffer : public BufferObject
    {
    public:
        explicit Buffer(std::span<const T> data)
            : BufferObject{ static_cast<gl::size_t>(data.size_bytes()) }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(
                m_handle, 
                glf::Buffer::StorageFlags::DynamicStorage | 
                glf::Buffer::StorageFlags::MapRead        | 
                glf::Buffer::StorageFlags::MapWrite       | 
                glf::Buffer::StorageFlags::MapPersistent  | 
                glf::Buffer::StorageFlags::MapCoherent    , 
                data);
        }
        explicit Buffer(gl::count_t count)
            : BufferObject{ static_cast<gl::size_t>(count * sizeof(T)) }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(
                m_handle,
                glf::Buffer::StorageFlags::DynamicStorage |
                glf::Buffer::StorageFlags::MapRead        |
                glf::Buffer::StorageFlags::MapWrite       |
                glf::Buffer::StorageFlags::MapPersistent  |
                glf::Buffer::StorageFlags::MapCoherent    ,
                m_size);
        }
                 Buffer(Buffer&&) noexcept = default;
                ~Buffer()
        {
            gl::delete_buffer(m_handle);
        }

        void copy      (std::span<const T> data)
        {
            gl::buffer_data(m_handle, gl::offset_t{ 0u }, data);
        }
        void copy_range(std::span<const T> data, fox::offset_t offset)
        {
            gl::buffer_data(m_handle, offset, data);
        }

        void map()
        {

        }
        void read()
        {

        }
        void write()
        {

        }
        void unmap()
        {

        }

        gl::count_t count() const
        {
            return static_cast<gl::count_t>(m_size / sizeof(T));
        }

        Buffer& operator=(Buffer&&) noexcept = default;
    };



    template<typename T>
    class UniformBuffer : public BufferObject
    {
    public:
        explicit UniformBuffer(const T& data = {})
            : BufferObject{ sizeof(T) }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(m_handle, glf::Buffer::StorageFlags::DynamicStorage, std::span<const T>{ &data, 1u });
        }
                 UniformBuffer(UniformBuffer&&) noexcept = default;
                ~UniformBuffer()
        {
            gl::delete_buffer(m_handle);
        }

        void bind_index(gl::uint32_t index) const
        {
            gl::bind_buffer_base(m_handle, glf::Buffer::BaseTarget::UniformBuffer, index);
        }

        void copy(const T& data)
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

        UniformBuffer& operator=(UniformBuffer&&) noexcept = default;
    };
    template<typename T, fox::count_t N>
    class UniformArrayBuffer : public BufferObject
    {
    public:
        explicit UniformArrayBuffer()
            : BufferObject{ N * sizeof(T) }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(m_handle, glf::Buffer::StorageFlags::DynamicStorage, gl::size_t{ N * sizeof(T) });
        }
        explicit UniformArrayBuffer(std::span<const T> data)
            : BufferObject{ data.size_bytes() }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(m_handle, glf::Buffer::StorageFlags::DynamicStorage, data);
        }
                 UniformArrayBuffer(UniformArrayBuffer&&) noexcept = default;
                ~UniformArrayBuffer()
        {
            gl::delete_buffer(m_handle);
        }

        void bind_index(gl::uint32_t index) const
        {
            gl::bind_buffer_base(m_handle, glf::Buffer::BaseTarget::UniformBuffer, index);
        }
        void bind_index_range(gl::uint32_t index, fox::count_t count, gl::offset_t offset) const
        {
            gl::bind_buffer_range(m_handle, glf::Buffer::BaseTarget::UniformBuffer, index, gl::byterange_t{ count * sizeof(T), offset * sizeof(T) });
        }

        void copy(std::span<const T, N> data)
        {
            gl::buffer_data(m_handle, 0, std::span<const T>{ data.data(), data.size() });
        }
        void copy_index(fox::offset_t offset, const T& data)
        {
            if (offset + 1u > N) throw std::invalid_argument{ "Data exceeds buffer size!" };

            gl::buffer_data(m_handle, offset * sizeof(T), std::span<const T>{ &data, 1u });
        }
        void copy_range(fox::offset_t offset, std::span<const T> data)
        {
            if (offset + data.size() > N) throw std::invalid_argument{ "Data exceeds buffer size!" };

            gl::buffer_data(m_handle, offset * sizeof(T), data);
        }

        UniformArrayBuffer& operator=(UniformArrayBuffer&&) noexcept = default;
    };
}
