#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/Buffer/Buffer.hpp"

namespace fox::gfx::api::gl
{
    class BufferObject : public api::Buffer, public gl::Object
    {
    protected:
        BufferObject(fox::size_t size)
            : api::Buffer{ size } {}
        ~BufferObject() = default;
    };



    template<api::Buffer::Type TYPE, api::Buffer::Access ACCESS, typename T>
    class Buffer;

    template<api::Buffer::Type TYPE, typename T>
    class Buffer<TYPE, api::Buffer::Access::Static, T> : public BufferObject
    {
    public:
        explicit Buffer(std::span<const T> data)
            : BufferObject{ data.size_bytes() }
        {
            m_handle = gl::create_buffer();

            const auto& storageFlags = glf::Buffer::StorageFlags::None;
            gl::buffer_storage(m_handle, storageFlags, data);
        }
        ~Buffer()
        {
            gl::delete_buffer(m_handle);
        }

        fox::count_t count() const
        {
            return static_cast<fox::count_t>(m_size / sizeof(T));
        }

    protected:
        Buffer(fox::size_t size)
            : BufferObject{ size } {}
    };
    template<api::Buffer::Type TYPE, typename T>
    class Buffer<TYPE, api::Buffer::Access::Dynamic, T> : public Buffer<TYPE, api::Buffer::Access::Static, T>
    {
    public:
        explicit Buffer(fox::count_t count)
            : Buffer<TYPE, api::Buffer::Access::Static, T>{ count * sizeof(T) }
        {
            m_handle = gl::create_buffer();

            const auto& storageFlags = 
                glf::Buffer::StorageFlags::DynamicStorage | 
                glf::Buffer::StorageFlags::MapRead        | 
                glf::Buffer::StorageFlags::MapWrite       ;

            gl::buffer_storage(m_handle, storageFlags, m_size);
        }
        explicit Buffer(std::span<const T> data)
            : Buffer<TYPE, api::Buffer::Access::Static, T>{ data.size_bytes() }
        {
            m_handle = gl::create_buffer();

            const auto& storageFlags = 
                glf::Buffer::StorageFlags::DynamicStorage | 
                glf::Buffer::StorageFlags::MapRead        | 
                glf::Buffer::StorageFlags::MapWrite       ;

            gl::buffer_storage(m_handle, storageFlags, data);
        }
        ~Buffer() = default;

        void copy(std::span<const T> data)
        {
            gl::buffer_sub_data(m_handle, 0, data);
        }
        void copy_range(fox::offset_t offset, std::span<const T> data)
        {
            gl::buffer_sub_data(m_handle, offset * sizeof(T), data);
        }

        template<api::Buffer::Mapping MAPPING = api::Buffer::Mapping::ReadWrite>
        auto map()
        {
            const auto& bufferMapping = gl::map_buffer_mapping(MAPPING);
                  auto* data          = gl::map_buffer(m_handle, bufferMapping);

            using data_t = std::conditional_t<MAPPING == api::Buffer::Mapping::Read, const T, T>;
            return std::span<data_t>{ data, m_size / sizeof(T) };
        }
        template<api::Buffer::Mapping MAPPING = api::Buffer::Mapping::ReadWrite>
        auto map_range(fox::count_t count, fox::offset_t offset)
        {
            const auto& bufferMapping = gl::map_buffer_mapping(MAPPING);
                  auto* data          = gl::map_buffer_range(m_handle, bufferMapping, count * sizeof(T), offset * sizeof(T));

            using data_t = std::conditional_t<MAPPING == api::Buffer::Mapping::Read, const T, T>;
            return std::span<data_t>{ data, m_size / sizeof(T) };
        }
        void unmap()
        {
            gl::unmap_buffer(m_handle);
        }

    protected:
        using Buffer<TYPE, api::Buffer::Access::Static, T>::m_handle;
        using Buffer<TYPE, api::Buffer::Access::Static, T>::m_size;
    };
    template<typename T>
    class Buffer<api::Buffer::Type::Uniform, api::Buffer::Access::Dynamic, T> : public BufferObject
    {
    public:
        explicit Buffer(const T& data = {})
            : BufferObject{ sizeof(T) }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(m_handle, glf::Buffer::StorageFlags::DynamicStorage, std::span<const T>{ &data, 1u });
        }
        ~Buffer()
        {
            gl::delete_buffer(m_handle);
        }

        void bind_index(gl::index_t index) const
        {
            gl::bind_buffer_base(m_handle, glf::Buffer::IndexedTarget::UniformBuffer, index);
        }

        void copy(const T& data)
        {
            gl::buffer_sub_data(m_handle, 0, std::span<const T>{ &data, 1u });
        }
        template<typename... T>
        void copy_sub(fox::size_t offset, const std::tuple<T...>& data) //TODO: check if used with std::tie instead of std::make_tuple?
        {
            //This method lets you copy a tuple of any amount of types into an allocated buffer
            //There is no guarantee that a parameter pack will be evaluated in order of declaration, so it can not be used
            //Arguments in a braced initializer list eg. tuple{ myval1, myval2 }, are required to be evaluated first to last
            //This guarantees that the data will be copied into the uniform buffer in order

            std::array<fox::byte_t, (sizeof(T) + ... + 0u)> buffer{};

            std::apply([&buffer](auto&&... args)
                {
                    fox::size_t size{};
                    ((std::memcpy(buffer.data() + size, &args, sizeof(args)), size += sizeof(args)), ...);
                }, data);

            gl::buffer_sub_data(m_handle, offset, std::span<const fox::byte_t>{ buffer.data(), buffer.size() });
        }
    };

    //Not implemented
    template<typename T>
    class Buffer<api::Buffer::Type::Uniform, api::Buffer::Access::Static, T>;



    template<typename T, fox::count_t N>
    class UniformArrayBuffer : public BufferObject
    {
    public:
        explicit UniformArrayBuffer()
            : BufferObject{ N * sizeof(T) }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(m_handle, glf::Buffer::StorageFlags::DynamicStorage, gl::sizeptr_t{ N * sizeof(T) });
        }
        explicit UniformArrayBuffer(std::span<const T> data)
            : BufferObject{ data.size_bytes() }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(m_handle, glf::Buffer::StorageFlags::DynamicStorage, data);
        }
        ~UniformArrayBuffer()
        {
            gl::delete_buffer(m_handle);
        }

        void bind_index(gl::index_t index) const
        {
            gl::bind_buffer_base(m_handle, glf::Buffer::IndexedTarget::UniformBuffer, index);
        }
        void bind_index_range(gl::index_t binding, fox::count_t count, fox::offset_t offset) const
        {
            gl::bind_buffer_range(m_handle, glf::Buffer::IndexedTarget::UniformBuffer, binding, count * sizeof(T), offset * sizeof(T));
        }

        void copy(std::span<const T, N> data)
        {
            gl::buffer_sub_data(m_handle, 0, data);
        }
        void copy_index(fox::offset_t offset, const T& data)
        {
            if (offset + 1u > N) throw std::invalid_argument{ "Data exceeds buffer size!" };

            gl::buffer_sub_data(m_handle, offset, std::span<const T>{ &data, 1u });
        }
        void copy_range(fox::offset_t offset, std::span<const T> data)
        {
            if (offset + data.size() > N) throw std::invalid_argument{"Data exceeds buffer size!"};

            gl::buffer_sub_data(m_handle, offset, data);
        }
    };
}
