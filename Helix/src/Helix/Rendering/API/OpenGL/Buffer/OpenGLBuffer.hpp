#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Buffer/Buffer.hpp"
#include "Helix/Rendering/API/OpenGL/Internal/InternalView.hpp"

namespace hlx::gfx::api
{
    template<Buffer::Type TYPE, typename T>
    class GBuffer<GraphicsAPI::OpenGL, TYPE, Buffer::Access::Static, T> final : public Buffer
    {
    public:
        GBuffer(std::span<const T> data)
            : Buffer{ data.size_bytes() }
        {
            m_glId = gl::create_buffer();

            const auto& glAccess = gl::buffer_access(Buffer::Access::Static);
            gl::buffer_storage(m_glId, glAccess, data);
        }
        ~GBuffer()
        {
            gl::delete_buffer(m_glId);
        }

        void bind()
        {
            if constexpr (TYPE == Buffer::Type::Vertex)       gl::bind_buffer(m_glId, GL_ARRAY_BUFFER);
            if constexpr (TYPE == Buffer::Type::Index)        gl::bind_buffer(m_glId, GL_ELEMENT_ARRAY_BUFFER);
            if constexpr (TYPE == Buffer::Type::UniformArray) gl::bind_buffer(m_glId, GL_UNIFORM_BUFFER);
        }
        void bind_range(u32 binding, u32 count, u32 offset)  requires (TYPE == Buffer::Type::UniformArray)
        {
            gl::bind_buffer_range(m_glId, GL_UNIFORM_BUFFER, binding, count * sizeof(T), offset * sizeof(T));
        }

        auto expose_internals() const
        {
            return InternalView<GBuffer<GraphicsAPI::OpenGL, TYPE, Buffer::Access::Static, T>>
            {
                m_glId,
            };
        }

    private:
        GLuint m_glId{};
    };
    template<Buffer::Type TYPE, typename T>
    class GBuffer<GraphicsAPI::OpenGL, TYPE, Buffer::Access::Dynamic, T> final : public Buffer
    {
    public:
        GBuffer(u32 count)
            : Buffer{ count * sizeof(T) }
        {
            m_glId = gl::create_buffer();

            const auto& glAccess = gl::buffer_access(Buffer::Access::Dynamic);
            gl::buffer_storage(m_glId, glAccess, m_size);
        }
        GBuffer(std::span<const T> data)
            : Buffer{ data.size_bytes() }
        {
            m_glId = gl::create_buffer();

            const auto& glAccess = gl::buffer_access(Buffer::Access::Dynamic);
            gl::buffer_storage(m_glId, glAccess, data);
        }
        ~GBuffer()
        {
            gl::delete_buffer(m_glId);
        }

        void bind()
        {
            if constexpr (TYPE == Buffer::Type::Vertex)       gl::bind_buffer(m_glId, GL_ARRAY_BUFFER);
            if constexpr (TYPE == Buffer::Type::Index)        gl::bind_buffer(m_glId, GL_ELEMENT_ARRAY_BUFFER);
            if constexpr (TYPE == Buffer::Type::UniformArray) gl::bind_buffer(m_glId, GL_UNIFORM_BUFFER);
        }
        void bind_range(u32 binding, u32 count, u32 offset)  requires (TYPE == Buffer::Type::UniformArray)
        {
            gl::bind_buffer_range(m_glId, GL_UNIFORM_BUFFER, binding, count * sizeof(T), offset * sizeof(T));
        }

        void copy(std::span<const T> data)
        {
            gl::buffer_sub_data(m_glId, 0, std::span<const T>{ &data, 1u });
        }
        void copy_range(u32 offset, std::span<const T> data)
        {
            gl::buffer_sub_data(m_glId, offset * sizeof(T), data);
        }

        template<Buffer::Mapping MAP>
        auto map()
        {
            using data_t = std::conditional_t<MAP == Buffer::Mapping::Read, const T, T>;

            const auto& glMap = gl::buffer_map(MAP);
            auto* data = gl::map_buffer(m_glId, glMap);

            return std::span<data_t>{ data, m_size / sizeof(T) };
        }
        template<Buffer::Mapping MAP>
        auto map_range(u32 count, u32 offset)
        {
            using data_t = std::conditional_t<MAP == Buffer::Mapping::Read, const T, T>;

            const auto& glMap = gl::buffer_map(MAP);
            auto* data = gl::map_buffer_range(m_glId, glMap, count * sizeof(T), offset * sizeof(T));

            return std::span<data_t>{ data, m_size / sizeof(T) };
        }
        bool unmap()
        {
            if (!gl::unmap_buffer(m_glId)) throw std::runtime_error{ "Buffer data store may be undefined!" };
        }

        auto expose_internals() const
        {
            return InternalView<GBuffer<GraphicsAPI::OpenGL, TYPE, Buffer::Access::Dynamic, T>>
            {
                m_glId,
            };
        }

    private:
        GLuint m_glId{};
    };
    template<typename T>
    class GBuffer<GraphicsAPI::OpenGL, Buffer::Type::Uniform, Buffer::Access::Dynamic, T> final : public Buffer
    {
    public:
        GBuffer(const T& data)
        {
            m_glId = gl::create_buffer();

            const auto& glAccess = gl::buffer_access(Buffer::Access::Dynamic);
            gl::buffer_storage(m_glId, glAccess, std::span<const T>{ &data, 1u });
        }
        ~GBuffer()
        {
            gl::delete_buffer(m_glId);
        }

        void bind(u32 binding)
        {
            gl::bind_buffer_base(m_glId, GL_UNIFORM_BUFFER, binding);
        }

        void copy(const T& data)
        {
            gl::buffer_sub_data(m_glId, 0, std::span<const T>{ &data, 1u });
        }

        auto expose_internals() const
        {
            return InternalView<GBuffer<GraphicsAPI::OpenGL, Buffer::Type::Uniform, Buffer::Access::Dynamic, T>>
            {
                m_glId,
            };
        }

    private:
        GLuint m_glId{};
    };
    template<typename T>
    class GBuffer<GraphicsAPI::OpenGL, Buffer::Type::Uniform, Buffer::Access::Static, T>;
}
