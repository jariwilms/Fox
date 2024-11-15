#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/GL.hpp"
#include "Fox/Rendering/API/OpenGL/Buffer/OpenGLBuffer.hpp"
#include "Fox/Rendering/API/OpenGL/Layout/OpenGLVertexLayout.hpp"

namespace fox::gfx::api::gl
{
    class OpenGLVertexArray : public gl::Object
    {
    public:
        template<api::Buffer::Access ACCESS, typename T>
        using vertex_t             = OpenGLBuffer<api::Buffer::Type::Vertex, ACCESS, T>;
        template<api::Buffer::Access ACCESS>
        using index_t              = OpenGLBuffer<api::Buffer::Type::Index, ACCESS, std::uint32_t>;
        template<api::Buffer::Access ACCESS, typename T>
        using vertex_pointer       = std::shared_ptr<vertex_t<ACCESS, T>>;
        template<api::Buffer::Access ACCESS, typename T>
        using const_vertex_pointer = std::shared_ptr<const vertex_t<ACCESS, T>>;
        using const_index_pointer  = std::shared_ptr<const index_t<api::Buffer::Access::Static>>;

        OpenGLVertexArray()
        {
            m_handle = gl::create_vertex_array();
        }
        OpenGLVertexArray(OpenGLVertexArray&& other) noexcept
        {
            *this = std::move(other);
        }
        ~OpenGLVertexArray()
        {
            gl::delete_vertex_array(m_handle);
        }

        void bind()
        {
            gl::bind_vertex_array(m_handle);
        }

        template<api::Buffer::Access ACCESS, typename T, typename... U>
        void tie(vertex_pointer<ACCESS, T> buffer, OpenGLVertexLayout<U...> layout)
        {
            tie(static_pointer_cast<const vertex_t<ACCESS, T>>(buffer), layout);
        }
        template<api::Buffer::Access ACCESS, typename T, typename... U>
        void tie(const_vertex_pointer<ACCESS, T> buffer, OpenGLVertexLayout<U...> layout)
        {
            if (m_glArrayBindingIndex > static_cast<GLuint>(gl::integer_v(GL_MAX_VERTEX_ATTRIBS))) throw std::runtime_error{ "Maximum vertex attributes exceeded!" };

            gl::vertex_array_vertex_buffer(m_handle, buffer->handle(), m_glArrayBindingIndex, static_cast<GLsizei>(layout.stride()));

            GLuint offset{};
            for (const auto& attribute : layout.attributes())
            {
                gl::enable_vertex_array_attribute(m_handle, m_glArrayAttributeIndex);
                gl::vertex_array_attribute_format(m_handle, m_glArrayAttributeIndex, offset, attribute.glType, static_cast<GLint>(attribute.stride()), attribute.isNormalized);
                gl::vertex_array_attribute_binding(m_handle, m_glArrayAttributeIndex, m_glArrayBindingIndex);

                offset += static_cast<GLuint>(attribute.stride());
                m_primitiveCount += static_cast<std::uint32_t>(buffer->size() / attribute.stride());

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

        OpenGLVertexArray& operator=(OpenGLVertexArray&& other) noexcept
        {
            m_handle                  = other.m_handle;
            m_glArrayAttributeIndex = other.m_glArrayAttributeIndex;
            m_glArrayBindingIndex   = other.m_glArrayBindingIndex;
            m_primitiveCount        = other.m_primitiveCount;

            other.m_handle                = {};
            other.m_glArrayAttributeIndex = 0u;
            other.m_glArrayBindingIndex   = 0u;
            other.m_primitiveCount        = 0u;

            return *this;
        }

    private:
        GLuint m_glArrayAttributeIndex{};
        GLuint m_glArrayBindingIndex{};

        const_index_pointer m_indexBuffer{};
        std::uint32_t m_primitiveCount{};
    };
}
