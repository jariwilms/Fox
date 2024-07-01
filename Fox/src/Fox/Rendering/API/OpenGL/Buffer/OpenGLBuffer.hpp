#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/GL.hpp"
#include "Fox/Rendering/API/OpenGL/Internal/InternalView.hpp"
#include "Fox/Rendering/API/Implementation/GBuffer.hpp"
#include "Fox/Rendering/Buffer/Buffer.hpp"
#include "Fox/Core/Library/Utility/Utility.hpp"

namespace fox::gfx::imp::api
{
    template<Buffer::Type TYPE, typename T>
    class GBuffer<gfx::api::GraphicsAPI::OpenGL, TYPE, Buffer::Access::Static, T> : public gfx::api::Buffer
    {
    public:
        GBuffer(std::span<const T> data)
            : Buffer{ data.size_bytes() }
        {
            m_glId = gl::create_buffer();

            const auto& glAccess = gl::map_buffer_access(Buffer::Access::Static);
            gl::buffer_storage(m_glId, glAccess, data);
        }
        GBuffer(GBuffer&& other) noexcept
        {
            *this = std::move(other);
        }
        virtual ~GBuffer()
        {
            if (m_glId) gl::delete_buffer(m_glId);
        }

        void bind() const
        {
            if constexpr (TYPE == Buffer::Type::Vertex)       gl::bind_buffer(m_glId, gl::Buffer::Target::ArrayBuffer);
            if constexpr (TYPE == Buffer::Type::Index)        gl::bind_buffer(m_glId, gl::Buffer::Target::ElementArrayBuffer);
            if constexpr (TYPE == Buffer::Type::UniformArray) gl::bind_buffer(m_glId, gl::Buffer::Target::UniformBuffer);
        }
        void bind_range(std::uint32_t binding, std::uint32_t count, std::uint32_t offset) const requires (TYPE == Buffer::Type::UniformArray)
        {
            gl::bind_buffer_range(m_glId, GL_UNIFORM_BUFFER, binding, count * sizeof(T), offset * sizeof(T));
        }

        std::uint32_t count() const
        {
            return static_cast<std::uint32_t>(m_size / sizeof(T));
        }

        auto expose_internals() const
        {
            return InternalView<GBuffer<gfx::api::GraphicsAPI::OpenGL, TYPE, Buffer::Access::Static, T>>
            {
                m_glId
            };
        }

        GBuffer& operator=(GBuffer&& other) noexcept
        {
            m_glId = other.m_glId;

            other.m_glId = 0u;

            return *this;
        }

    protected:
        GBuffer(size_t size)
            : Buffer{ size } {}

        GLuint m_glId{};
    };
    template<Buffer::Type TYPE, typename T>
    class GBuffer<gfx::api::GraphicsAPI::OpenGL, TYPE, Buffer::Access::Dynamic, T> final : public GBuffer<gfx::api::GraphicsAPI::OpenGL, TYPE, Buffer::Access::Static, T>
    {
    public:
        GBuffer(std::uint32_t count)
            : GBuffer<gfx::api::GraphicsAPI::OpenGL, TYPE, Buffer::Access::Static, T>{ count * sizeof(T) }
        {
            this->m_glId = gl::create_buffer();

            gl::buffer_storage(this->m_glId, gl::Buffer::StorageFlags::DynamicStorage, this->m_size);
        }
        GBuffer(std::span<const T> data)
            : GBuffer<gfx::api::GraphicsAPI::OpenGL, TYPE, Buffer::Access::Static, T>{ data.size_bytes() }
        {
            this->m_glId = gl::create_buffer();

            const auto& glAccess = gl::map_buffer_access(Buffer::Access::Dynamic);
            gl::buffer_storage(this->m_glId, glAccess, data);
        }
        GBuffer(GBuffer&& other) noexcept
        {
            *this = std::move(other);
        }
        ~GBuffer() = default;

        void copy(std::span<const T> data)
        {
            gl::buffer_sub_data(this->m_glId, 0, data);
        }
        void copy_range(std::uint32_t offset, std::span<const T> data)
        {
            gl::buffer_sub_data(this->m_glId, offset * sizeof(T), data);
        }

        template<Buffer::Mapping MAPPING>
        auto map()
        {
            using data_t = std::conditional_t<MAPPING == Buffer::Mapping::Read, const T, T>;

            const auto& glMap = gl::map_buffer_mapping(MAPPING);
            auto* data        = gl::map_buffer(this->m_glId, glMap);

            return std::span<data_t>{ data, this->m_size / sizeof(T) };
        }
        template<Buffer::Mapping MAPPING>
        auto map_range(std::uint32_t count, std::uint32_t offset)
        {
            using data_t = std::conditional_t<MAPPING == Buffer::Mapping::Read, const T, T>;

            const auto& glMap = gl::map_buffer_mapping(MAPPING);
            auto* data        = gl::map_buffer_range(this->m_glId, glMap, count * sizeof(T), offset * sizeof(T));

            return std::span<data_t>{ data, this->m_size / sizeof(T) };
        }
        bool unmap()
        {
            if (!gl::unmap_buffer(this->m_glId)) throw std::runtime_error{ "Buffer data store may be undefined!" };
        }

        GBuffer& operator=(GBuffer&& other) noexcept
        {
            return GBuffer<gfx::api::GraphicsAPI::OpenGL, TYPE, Buffer::Access::Static, T>::operator=(std::move(other));
        }
    };
    template<typename T>
    class GBuffer<gfx::api::GraphicsAPI::OpenGL, Buffer::Type::Uniform, Buffer::Access::Dynamic, T> final : public Buffer
    {
    public:
        GBuffer()
            : Buffer{ sizeof(T) }
        {
            m_glId = gl::create_buffer();

            gl::buffer_storage(m_glId, gl::Buffer::StorageFlags::DynamicStorage, sizeof(T) );
        }
        GBuffer(const T& data)
            : Buffer{ sizeof(T) }
        {
            m_glId = gl::create_buffer();

            const auto& glAccess = gl::map_buffer_access(Buffer::Access::Dynamic);
            gl::buffer_storage(m_glId, glAccess, std::span<const T>{ &data, 1u });
        }
        GBuffer(GBuffer&& other) noexcept
        {
            *this = std::move(other);
        }
        ~GBuffer()
        {
            if (m_glId) gl::delete_buffer(m_glId);
        }

        void bind(std::uint32_t binding) const
        {
            gl::bind_buffer_base(m_glId, gl::Buffer::TargetBase::UniformBuffer, binding);
        }

        void copy(const T& data)
        {
            gl::buffer_sub_data(m_glId, 0, std::span<const T>{ &data, 1u });
        }
        template<typename... T>
        void copy_tuple(size_t offset, const std::tuple<T...>& data)
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

            gl::buffer_sub_data(m_glId, offset, std::span<const byte>{ buffer.data(), buffer.size() });
        }

        auto expose_internals() const
        {
            return InternalView<GBuffer<gfx::api::GraphicsAPI::OpenGL, Buffer::Type::Uniform, Buffer::Access::Dynamic, T>>
            {
                m_glId
            };
        }

        GBuffer& operator=(GBuffer&& other) noexcept
        {
            m_glId = other.m_glId;

            other.m_glId = 0;

            return *this;
        }

    private:
        GLuint m_glId{};
    };
    template<typename T>
    class GBuffer<gfx::api::GraphicsAPI::OpenGL, Buffer::Type::Uniform, Buffer::Access::Static, T>;
}
