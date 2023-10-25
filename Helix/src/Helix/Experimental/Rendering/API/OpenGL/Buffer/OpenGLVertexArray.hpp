#pragma once

#include "Helix/Experimental/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Buffer/OpenGLBuffer.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Layout/OpenGLVertexLayout.hpp"
#include "Helix/Experimental/Rendering/Buffer/VertexArray.hpp"

namespace hlx::gfx::api
{
    template<>
    class GVertexArray<GraphicsAPI::OpenGL> final : public VertexArray
    {
    public:
        template<typename T>
        using vertex_type          = GBuffer<GraphicsAPI::OpenGL, Buffer::Type::Vertex, T>;
        using index_type           = GBuffer<GraphicsAPI::OpenGL, Buffer::Type::Index, u32>;
        template<typename T>
        using vertex_pointer       = std::shared_ptr<vertex_type<T>>;
        template<typename T>
        using const_vertex_pointer = std::shared_ptr<const vertex_type<T>>;
        using const_index_pointer  = std::shared_ptr<const index_type>;

        GVertexArray()
        {
            //m_glId = gl::create_vertex_array();
        }
        ~GVertexArray()
        {
            gl::delete_vertex_array(m_glId);
        }

        void bind()
        {
            gl::bind_vertex_array(m_glId);
        }

        template<typename T, typename... U>
        void tie(vertex_pointer<T> buffer, VertexLayout<GraphicsAPI::OpenGL, U...> layout)
        {
            tie(static_pointer_cast<const vertex_type<T>>(buffer), layout);
        }
        template<typename T, typename... U>
        void tie(const_vertex_pointer<T> buffer, VertexLayout<GraphicsAPI::OpenGL, U...> layout)
        {
            if (m_glArrayBindingIndex > static_cast<GLuint>(gl::integer_v(GL_MAX_VERTEX_ATTRIBS))) throw std::runtime_error{ "Maximum vertex attributes exceeded!" };

            gl::vertex_array_vertex_buffer(m_glId, buffer->id(), m_glArrayBindingIndex, static_cast<GLsizei>(layout.stride()));

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

        unsigned int primitive_count() const
        {
            return m_primitiveCount;
        }

        GLuint id() const
        {
            return m_glId;
        }

    private:
        GLuint m_glId{};
        GLuint m_glArrayAttributeIndex{};
        GLuint m_glArrayBindingIndex{};

        const_index_pointer m_indexBuffer{};
        u32 m_primitiveCount{};
    };
}
