#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Layout/OpenGLVertexLayout.hpp"
#include "Helix/Rendering/Buffer/VertexArray.hpp"

namespace hlx::gfx::api
{
    template<>
    class GVertexArray<GraphicsAPI::OpenGL> final : public VertexArray
    {
    public:
        template<Buffer::Access ACCESS, typename T>
        using vertex_type          = GBuffer<GraphicsAPI::OpenGL, Buffer::Type::Vertex, ACCESS, T>;
        template<Buffer::Access ACCESS>
        using index_type           = GBuffer<GraphicsAPI::OpenGL, Buffer::Type::Index, ACCESS, u32>;
        template<Buffer::Access ACCESS, typename T>
        using vertex_pointer       = std::shared_ptr<vertex_type<ACCESS, T>>;
        template<Buffer::Access ACCESS, typename T>
        using const_vertex_pointer = std::shared_ptr<const vertex_type<ACCESS, T>>;
        template<Buffer::Access ACCESS>
        using const_index_pointer  = std::shared_ptr<const index_type<ACCESS>>;

        GVertexArray()
        {
            m_glId = gl::create_vertex_array();
        }
        ~GVertexArray()
        {
            gl::delete_vertex_array(m_glId);
        }

        void bind()
        {
            gl::bind_vertex_array(m_glId);
        }

        template<Buffer::Access ACCESS, typename T, typename... U>
        void tie(vertex_pointer<ACCESS, T> buffer, GVertexLayout<GraphicsAPI::OpenGL, U...> layout)
        {
            tie(static_pointer_cast<const vertex_type<ACCESS, T>>(buffer), layout);
        }
        template<Buffer::Access ACCESS, typename T, typename... U>
        void tie(const_vertex_pointer<ACCESS, T> buffer, GVertexLayout<GraphicsAPI::OpenGL, U...> layout)
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
        template<Buffer::Access ACCESS>
        void tie(const_index_pointer<ACCESS> buffer)
        {
            throw std::logic_error{ "The method or operation has not been implemented!" };
        }

        unsigned int primitive_count() const
        {
            return m_primitiveCount;
        }

    private:
        GLuint m_glId{};
        GLuint m_glArrayAttributeIndex{};
        GLuint m_glArrayBindingIndex{};

        u32 m_primitiveCount{};
    };
}
