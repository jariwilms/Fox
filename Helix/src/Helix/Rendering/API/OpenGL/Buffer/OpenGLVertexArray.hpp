#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/GL.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Layout/OpenGLVertexLayout.hpp"
#include "Helix/Rendering/API/Implementation/GVertexArray.hpp"
#include "Helix/Rendering/Buffer/VertexArray.hpp"

namespace hlx::gfx::imp::api
{
    template<>
    class GVertexArray<gfx::api::GraphicsAPI::OpenGL> final : public gfx::api::VertexArray
    {
    public:
        template<Buffer::Access ACCESS, typename T>
        using vertex_type = GBuffer<gfx::api::GraphicsAPI::OpenGL, Buffer::Type::Vertex, ACCESS, T>;
        template<Buffer::Access ACCESS>
        using index_type           = GBuffer<gfx::api::GraphicsAPI::OpenGL, Buffer::Type::Index, ACCESS, u32>;
        template<Buffer::Access ACCESS, typename T>
        using vertex_pointer       = std::shared_ptr<vertex_type<ACCESS, T>>;
        template<Buffer::Access ACCESS, typename T>
        using const_vertex_pointer = std::shared_ptr<const vertex_type<ACCESS, T>>;
        using const_index_pointer  = std::shared_ptr<const index_type<Buffer::Access::Static>>;

        GVertexArray()
        {
            m_glId = gl::create_vertex_array();
        }
        GVertexArray(GVertexArray&& other) noexcept
        {
            *this = std::move(other);
        }
        ~GVertexArray()
        {
            if (m_glId) gl::delete_vertex_array(m_glId);
        }

        void bind()
        {
            gl::bind_vertex_array(m_glId);
        }

        template<Buffer::Access ACCESS, typename T, typename... U>
        void tie(vertex_pointer<ACCESS, T> buffer, GVertexLayout<gfx::api::GraphicsAPI::OpenGL, U...> layout)
        {
            tie(static_pointer_cast<const vertex_type<ACCESS, T>>(buffer), layout);
        }
        template<Buffer::Access ACCESS, typename T, typename... U>
        void tie(const_vertex_pointer<ACCESS, T> buffer, GVertexLayout<gfx::api::GraphicsAPI::OpenGL, U...> layout)
        {
            if (m_glArrayBindingIndex > static_cast<GLuint>(gl::integer_v(GL_MAX_VERTEX_ATTRIBS))) throw std::runtime_error{ "Maximum vertex attributes exceeded!" };

            gl::vertex_array_vertex_buffer(m_glId, buffer->expose_internals().glId, m_glArrayBindingIndex, static_cast<GLsizei>(layout.stride()));

            GLuint offset{};
            for (const auto& attribute : layout.attributes())
            {
                gl::enable_vertex_array_attribute(m_glId, m_glArrayAttributeIndex);
                gl::vertex_array_attribute_format(m_glId, m_glArrayAttributeIndex, offset, attribute.glType, static_cast<GLint>(attribute.stride()), attribute.isNormalized);
                gl::vertex_array_attribute_binding(m_glId, m_glArrayAttributeIndex, m_glArrayBindingIndex);

                offset += static_cast<GLuint>(attribute.stride());
                m_primitiveCount += static_cast<u32>(buffer->size() / attribute.stride());

                ++m_glArrayAttributeIndex;
            }

            ++m_glArrayBindingIndex;
        }
        void tie(const_index_pointer buffer)
        {
            m_indexBuffer = buffer;
        }

        bool                is_indexed()      const
        {
            return m_indexBuffer.get() != nullptr;
        }
        const_index_pointer index_buffer()    const
        {
            return m_indexBuffer;
        }
        unsigned int        primitive_count() const
        {
            return m_primitiveCount;
        }

        GVertexArray& operator=(GVertexArray&& other) noexcept
        {
            m_glId                  = other.m_glId;
            m_glArrayAttributeIndex = other.m_glArrayAttributeIndex;
            m_glArrayBindingIndex   = other.m_glArrayBindingIndex;
            m_primitiveCount        = other.m_primitiveCount;

            other.m_glId                  = 0u;
            other.m_glArrayAttributeIndex = 0u;
            other.m_glArrayBindingIndex   = 0u;
            other.m_primitiveCount        = 0u;

            return *this;
        }

    private:
        GLuint m_glId{};
        GLuint m_glArrayAttributeIndex{};
        GLuint m_glArrayBindingIndex{};

        const_index_pointer m_indexBuffer{};
        u32 m_primitiveCount{};
    };
}
