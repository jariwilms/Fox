#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/API/OpenGL/Buffer/Buffer.hpp"
#include "Fox/Rendering/API/OpenGL/Layout/VertexLayout.hpp"

namespace fox::gfx::api::gl
{
    class VertexArray : public gl::Object
    {
    public:
        template<api::Buffer::Access ACCESS, typename T>
        using vertex_t             = Buffer<api::Buffer::Type::Vertex, ACCESS, T>;
        template<api::Buffer::Access ACCESS>
        using index_t              = Buffer<api::Buffer::Type::Index, ACCESS, std::uint32_t>;
        template<api::Buffer::Access ACCESS, typename T>
        using vertex_pointer       = std::shared_ptr<vertex_t<ACCESS, T>>;
        template<api::Buffer::Access ACCESS, typename T>
        using const_vertex_pointer = std::shared_ptr<const vertex_t<ACCESS, T>>;
        using const_index_pointer  = std::shared_ptr<const index_t<api::Buffer::Access::Static>>;

        VertexArray()
        {
            m_handle = gl::create_vertex_array();
        }
        VertexArray(VertexArray&& other) noexcept
        {
            *this = std::move(other);
        }
        ~VertexArray()
        {
            gl::delete_vertex_array(m_handle);
        }

        void bind()
        {
            gl::bind_vertex_array(m_handle);
        }

        template<api::Buffer::Access ACCESS, typename T, typename... U>
        void tie(vertex_pointer<ACCESS, T> buffer, VertexLayout<U...> layout)
        {
            tie(static_pointer_cast<const vertex_t<ACCESS, T>>(buffer), layout);
        }
        template<api::Buffer::Access ACCESS, typename T, typename... U>
        void tie(const_vertex_pointer<ACCESS, T> buffer, VertexLayout<U...> layout)
        {
            //TODO: this value (MaxVertexAttribs) should be pulled from gl::State Object
            //if (m_arrayBindingIndex > static_cast<gl::uint32_t>(gl::integer_v(GL_MAX_VERTEX_ATTRIBS))) throw std::runtime_error{ "Maximum vertex attributes exceeded!" };

            gl::vertex_array_vertex_buffer(m_handle, buffer->handle(), m_arrayBindingIndex, static_cast<gl::size_t>(layout.stride()));

            gl::uint32_t offset{};
            for (const auto& attribute : layout.attributes())
            {
                gl::enable_vertex_array_attribute(m_handle, m_arrayAttributeIndex);
                gl::vertex_array_attribute_format(m_handle, m_arrayAttributeIndex, offset, attribute.type, attribute.count, attribute.isNormalized);
                gl::vertex_array_attribute_binding(m_handle, m_arrayAttributeIndex, m_arrayBindingIndex);

                offset           += static_cast<gl::uint32_t>(attribute.stride());
                m_primitiveCount += static_cast<fox::uint32_t>(buffer->size() / attribute.stride());

                ++m_arrayAttributeIndex;
            }

            ++m_arrayBindingIndex;
        }
        void tie(const_index_pointer buffer)
        {
            m_indexBuffer = buffer;
            gl::vertex_array_element_buffer(m_handle, m_indexBuffer->handle());
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

        VertexArray& operator=(VertexArray&& other) noexcept
        {
            m_handle              = other.m_handle;
            m_arrayAttributeIndex = other.m_arrayAttributeIndex;
            m_arrayBindingIndex   = other.m_arrayBindingIndex;
            m_primitiveCount      = other.m_primitiveCount;
            m_indexBuffer         = std::move(other.m_indexBuffer);

            other.m_handle              = {};
            other.m_arrayAttributeIndex = 0u;
            other.m_arrayBindingIndex   = 0u;
            other.m_primitiveCount      = 0u;
            other.m_indexBuffer.reset();

            return *this;
        }

    private:
        gl::uint32_t m_arrayAttributeIndex{};
        gl::uint32_t m_arrayBindingIndex{};

        const_index_pointer m_indexBuffer{};
        fox::uint32_t m_primitiveCount{};
    };
}
