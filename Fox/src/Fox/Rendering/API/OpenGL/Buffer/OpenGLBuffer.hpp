#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/GL.hpp"
#include "Fox/Rendering/Buffer/Buffer.hpp"

namespace fox::gfx::api::gl
{
    template<api::Buffer::Type TYPE, api::Buffer::Access ACCESS, typename T>
    class OpenGLBuffer;

    template<api::Buffer::Type TYPE, typename T>
    class OpenGLBuffer<TYPE, api::Buffer::Access::Static, T> : public api::Buffer, public gl::Object
    {
    public:
        explicit OpenGLBuffer(std::span<const T> data)
            : api::Buffer{ data.size_bytes() }
        {
            m_handle = gl::create_buffer();

            const auto& accessFlags = gl::map_buffer_access(api::Buffer::Access::Static);
            gl::buffer_storage(m_handle, accessFlags, data);
        }
        OpenGLBuffer(OpenGLBuffer&& other) noexcept
        {
            *this = std::move(other);
        }
        virtual ~OpenGLBuffer()
        {
            gl::delete_buffer(m_handle);
        }

        void bind() const
        {
            if constexpr (TYPE == api::Buffer::Type::Vertex)       gl::bind_buffer(m_handle, gl::Buffer::Target::ArrayBuffer);
            if constexpr (TYPE == api::Buffer::Type::Index)        gl::bind_buffer(m_handle, gl::Buffer::Target::ElementArrayBuffer);
            if constexpr (TYPE == api::Buffer::Type::UniformArray) gl::bind_buffer(m_handle, gl::Buffer::Target::UniformBuffer);
        }
        void bind_range(std::uint32_t binding, std::uint32_t count, std::uint32_t offset) const requires (TYPE == api::Buffer::Type::UniformArray)
        {
            gl::bind_buffer_range(m_handle, GL_UNIFORM_BUFFER, binding, count * sizeof(T), offset * sizeof(T));
        }

        std::uint32_t count() const
        {
            return static_cast<std::uint32_t>(m_size / sizeof(T));
        }

        OpenGLBuffer& operator=(OpenGLBuffer&& other) noexcept
        {
            m_handle = other.m_handle;

            other.m_handle = {};

            return *this;
        }

    protected:
        OpenGLBuffer(size_t size)
            : api::Buffer{ size } {}
    };
    template<api::Buffer::Type TYPE, typename T >
    class OpenGLBuffer<TYPE, api::Buffer::Access::Dynamic, T> : public OpenGLBuffer<TYPE, api::Buffer::Access::Static, T>
    {
    public:
        OpenGLBuffer(std::uint32_t count)
            : OpenGLBuffer<TYPE, api::Buffer::Access::Static, T>{ count * sizeof(T) }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(m_handle, gl::Buffer::StorageFlags::DynamicStorage, m_size);
        }
        OpenGLBuffer(std::span<const T> data)
            : OpenGLBuffer<TYPE, api::Buffer::Access::Static, T>{ data }
        {
            m_handle = gl::create_buffer();

            const auto& accessFlags = gl::map_buffer_access(api::Buffer::Access::Dynamic);
            gl::buffer_storage(m_handle, accessFlags, data);
        }
        OpenGLBuffer(OpenGLBuffer&& other) noexcept
        {
            *this = std::move(other);
        }
        ~OpenGLBuffer() = default;

        void copy(std::span<const T> data)
        {
            gl::buffer_sub_data(m_handle, 0, data);
        }
        void copy_range(std::uint32_t offset, std::span<const T> data)
        {
            gl::buffer_sub_data(m_handle, offset * sizeof(T), data);
        }

        template<api::Buffer::Mapping MAPPING = api::Buffer::Mapping::ReadWrite>
        auto map()
        { 
            const auto& bufferMapping = gl::map_buffer_mapping(MAPPING);
            auto* data = gl::map_buffer(m_handle, bufferMapping);

            using data_t = std::conditional_t<MAPPING == api::Buffer::Mapping::Read, const T, T>;
            return std::span<data_t>{ data, m_size / sizeof(T) };
        }
        template<api::Buffer::Mapping MAPPING = api::Buffer::Mapping::ReadWrite>
        auto map_range(std::uint32_t count, std::uint32_t offset)
        {
            using data_t = std::conditional_t<MAPPING == api::Buffer::Mapping::Read, const T, T>;

            const auto& bufferMapping = gl::map_buffer_mapping(MAPPING);
            auto* data = gl::map_buffer_range(m_handle, bufferMapping, count * sizeof(T), offset * sizeof(T));

            return std::span<data_t>{ data, m_size / sizeof(T) };
        }
        void unmap()
        {
            if (!gl::unmap_buffer(m_handle)) throw std::runtime_error{ "Buffer data store may be undefined!" };
        }

        OpenGLBuffer& operator=(OpenGLBuffer&& other) noexcept
        {
            return OpenGLBuffer<TYPE, api::Buffer::Access::Static, T>::operator=(std::move(other));
        }

    protected:
        using OpenGLBuffer<TYPE, api::Buffer::Access::Static, T>::m_handle;
        using OpenGLBuffer<TYPE, api::Buffer::Access::Static, T>::m_size;
    };
    template<typename T>
    class OpenGLBuffer<api::Buffer::Type::Uniform, api::Buffer::Access::Dynamic, T> : public api::Buffer, public gl::Object
    {
    public:
        OpenGLBuffer()
            : api::Buffer{ sizeof(T) }
        {
            m_handle = gl::create_buffer();

            gl::buffer_storage(m_handle, gl::Buffer::StorageFlags::DynamicStorage, sizeof(T));
        }
        OpenGLBuffer(const T& data)
            : api::Buffer{ sizeof(T) }
        {
            m_handle = gl::create_buffer();

            const auto& bufferAccess = gl::map_buffer_access(api::Buffer::Access::Dynamic);
            gl::buffer_storage(m_handle, bufferAccess, std::span<const T>{ &data, 1u });
        }
        OpenGLBuffer(OpenGLBuffer&& other) noexcept
        {
            *this = std::move(other);
        }
        ~OpenGLBuffer()
        {
            gl::delete_buffer(m_handle);
        }

        void bind(std::uint32_t binding) const
        {
            gl::bind_buffer_base(m_handle, gl::Buffer::TargetBase::UniformBuffer, binding);
        }

        void copy(const T& data)
        {
            gl::buffer_sub_data(m_handle, 0, std::span<const T>{ &data, 1u });
        }
        template<typename... T>
        void copy_tuple(size_t offset, const std::tuple<T...>& data) //TODO: check if used with std::tie instead of std::make_tuple?
        {
            //This method lets you copy a tuple of any amount of types into an allocated buffer
            //There is no guarantee that a parameter pack will be evaluated in order of declaration, so we cannot use T... as a regular parameter
            //Arguments in a braced initializer list eg. tuple{ myval1, myval2 }, are required to be evaluated first to last
            //This guarantees that the data will be copied into the uniform buffer in order

            std::array<byte, (sizeof(T) + ... + 0u)> buffer{};

            std::apply([&buffer](auto&&... args)
                {
                    size_t size{};
                    ((std::memcpy(buffer.data() + size, &args, sizeof(args)), size += sizeof(args)), ...);
                }, data);

            gl::buffer_sub_data(m_handle, offset, std::span<const byte>{ buffer.data(), buffer.size() });
        }

        OpenGLBuffer& operator=(OpenGLBuffer&& other) noexcept
        {
            m_handle = other.m_handle;

            other.m_handle = {};

            return *this;
        }
    };
}
