#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/Buffer/Buffer.hpp"

namespace fox::gfx::api::gl
{
    template<api::Buffer::Type TYPE>
    class BufferObject : public api::Buffer, public gl::Object
    {
    protected:
        BufferObject(fox::size_t size)
            : api::Buffer{ size } {}
    };

    template<api::Buffer::Type TYPE, typename T>
    class StaticBuffer : public BufferObject<TYPE>
    {
    public:
        explicit StaticBuffer(std::span<const T> data)
            : BufferObject<TYPE>{ data.size_bytes() }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(m_handle, glf::Buffer::StorageFlags::None, data);
        }
        StaticBuffer(StaticBuffer&&) noexcept = default;
        virtual ~StaticBuffer()
        {
            gl::delete_buffer(m_handle);
        }

        fox::count_t count() const
        {
            return static_cast<fox::count_t>(m_size / sizeof(T));
        }

        StaticBuffer& operator=(StaticBuffer&&) noexcept = default;

    protected:
        explicit StaticBuffer(fox::size_t size)
            : BufferObject<TYPE>{ size } {}

        using api::Buffer::m_size;
        using gl::Object::m_handle;
    };
    template<api::Buffer::Type TYPE, typename T>
    class DynamicBuffer final : public StaticBuffer<TYPE, T>
    {
    public:
        explicit DynamicBuffer(fox::count_t count)
            : StaticBuffer<TYPE, T>{ count * sizeof(T) }
        {
            m_handle = gl::create_buffer();

            glf::Buffer::StorageFlags storageFlags
            {
                glf::Buffer::StorageFlags::DynamicStorage | 
                glf::Buffer::StorageFlags::MapRead        | 
                glf::Buffer::StorageFlags::MapWrite       
            };

            gl::buffer_storage(m_handle, storageFlags, m_size);
        }
        explicit DynamicBuffer(std::span<const T> data)
            : StaticBuffer<TYPE, T>{ data.size_bytes() }
        {
            m_handle = gl::create_buffer();

            glf::Buffer::StorageFlags storageFlags
            {
                glf::Buffer::StorageFlags::DynamicStorage | 
                glf::Buffer::StorageFlags::MapRead        | 
                glf::Buffer::StorageFlags::MapWrite       
            };

            gl::buffer_storage(m_handle, storageFlags, data);
        }
        DynamicBuffer(DynamicBuffer&& other) noexcept
            : api::Buffer{ std::move(other) }, gl::Object{ std::move(other) }
        {
            m_mappedData = std::exchange(other.m_mappedData, {});
        }
        ~DynamicBuffer() override
        {
            if (m_mappedData) unmap();
        }

        void copy(std::span<const T> data)
        {
            gl::buffer_sub_data(m_handle, 0u, data);
        }
        void copy_range(fox::offset_t offset, std::span<const T> data)
        {
            const auto& byteOffset = offset * sizeof(T);
            if (byteOffset + data.size() >= m_size) throw std::invalid_argument{ "Data exceeds buffer size!" };

            gl::buffer_sub_data(m_handle, byteOffset, data);
        }

        template<api::Buffer::Mapping MAPPING = api::Buffer::Mapping::ReadWrite>
        auto map()
        {
            if (is_mapped()) throw std::runtime_error{ "Buffer is already mapped!" };

            const auto& bufferMapping = gl::map_buffer_mapping(MAPPING);
                  auto* data          = gl::map_buffer<T>(m_handle, bufferMapping);

            m_mappedData = std::make_shared<std::span<T>>(data, count());

            using data_t = std::conditional_t<MAPPING == api::Buffer::Mapping::Read, const T, T>;
            return std::weak_ptr<std::span<data_t>>{ m_mappedData };
        }
        template<api::Buffer::Mapping MAPPING = api::Buffer::Mapping::ReadWrite>
        auto map_range(fox::count_t elements, fox::offset_t offset)
        {
            if (is_mapped())                  throw std::runtime_error{ "Buffer is already mapped!" };
            if (elements + offset >= count()) throw std::invalid_argument{ "Data size and/or offset too large!" };

            const auto& bufferMapping = gl::map_buffer_mapping(MAPPING);
                  auto* data          = gl::map_buffer_range<T>(m_handle, bufferMapping, elements * sizeof(T), offset * sizeof(T));

            m_mappedData = std::make_shared<std::span<T>>(data, count());

            using data_t = std::conditional_t<MAPPING == api::Buffer::Mapping::Read, const T, T>;
            return std::weak_ptr<std::span<data_t>>{ m_mappedData };
        }
        void unmap()
        {
            m_mappedData.reset();

            gl::unmap_buffer(m_handle);
        }

        fox::bool_t is_mapped() const
        {
            return static_cast<fox::bool_t>(m_mappedData);
        }

        DynamicBuffer& operator=(DynamicBuffer&& other) noexcept
        {
            if (this != &other)
            {
                StaticBuffer<TYPE, T>::operator=(std::move(other));

                m_mappedData = std::exchange(other.m_mappedData, m_mappedData);
            }

            return *this;
        }

    protected:
        using api::Buffer::m_size;
        using gl::Object::m_handle;
        using StaticBuffer<TYPE, T>::count;

        std::shared_ptr<std::span<T>> m_mappedData{};
    };

    template<typename T>
    class UniformBuffer : public BufferObject<api::Buffer::Type::Uniform>
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

        void bind_index(gl::index_t index) const
        {
            gl::bind_buffer_base(m_handle, glf::Buffer::BaseTarget::UniformBuffer, index);
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

        UniformBuffer& operator=(UniformBuffer&&) noexcept = default;
    };
    template<typename T, fox::count_t N>
    class UniformArrayBuffer : public BufferObject<api::Buffer::Type::Uniform>
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
        UniformArrayBuffer(UniformArrayBuffer&&) noexcept = default;
        ~UniformArrayBuffer()
        {
            gl::delete_buffer(m_handle);
        }

        void bind_index(gl::index_t index) const
        {
            gl::bind_buffer_base(m_handle, glf::Buffer::BaseTarget::UniformBuffer, index);
        }
        void bind_index_range(gl::index_t binding, fox::count_t count, fox::offset_t offset) const
        {
            gl::bind_buffer_range(m_handle, glf::Buffer::BaseTarget::UniformBuffer, binding, count * sizeof(T), offset * sizeof(T));
        }

        void copy(std::span<const T, N> data)
        {
            gl::buffer_sub_data(m_handle, 0, data);
        }
        void copy_index(fox::offset_t offset, const T& data)
        {
            if (offset + 1u > N) throw std::invalid_argument{ "Data exceeds buffer size!" };

            gl::buffer_sub_data(m_handle, offset * sizeof(T), std::span<const T>{ &data, 1u });
        }
        void copy_range(fox::offset_t offset, std::span<const T> data)
        {
            if (offset + data.size() > N) throw std::invalid_argument{ "Data exceeds buffer size!" };

            gl::buffer_sub_data(m_handle, offset * sizeof(T), data);
        }

        UniformArrayBuffer& operator=(UniformArrayBuffer&&) noexcept = default;
    };
}
