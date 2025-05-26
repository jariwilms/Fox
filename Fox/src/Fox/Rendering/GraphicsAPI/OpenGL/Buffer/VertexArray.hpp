#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/Layout/VertexLayout.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Buffer/Buffer.hpp"

namespace fox::gfx::api::gl
{
    class VertexArray : public gl::Object
    {
    public:
        VertexArray()
        {
            m_handle = gl::create_vertex_array();
        }
        VertexArray(VertexArray&&) noexcept = default;
        ~VertexArray()
        {
            gl::delete_vertex_array(m_handle);
        }

        void bind()
        {
            gl::bind_vertex_array(m_handle);
        }

        void enable_attribute (gl::index_t index)
        {
            gl::enable_vertex_array_attribute(m_handle, index);
        }
        void disable_attribute(gl::index_t index)
        {
            gl::disable_vertex_array_attribute(m_handle, index);
        }

        void tie(gl::handle_t vertexBuffer, const gfx::VertexLayout& layout)
        {
            gl::vertex_array_vertex_buffer(m_handle, vertexBuffer, m_bindingPoint, static_cast<gl::size_t>(layout.stride()), gl::index_t{ 0u });

            gl::offset_t offset{};
            for (const auto& attribute : layout.attributes())
            {
                enable_attribute(m_attributeIndex);

                gl::vertex_array_attribute_format (m_handle, m_attributeIndex, offset, gl::map_type(attribute.type), attribute.count, attribute.isNormalized);
                gl::vertex_array_attribute_binding(m_handle, m_attributeIndex, m_bindingPoint);
                if (attribute.isStatic) set_attribute_divisor(static_cast<gl::binding_t>(m_attributeIndex), attribute.divisionRate);

                offset += static_cast<gl::offset_t>(attribute.count * attribute.size);
                ++m_attributeIndex;
            }

            m_bindingPoint = gl::binding_t{ gl::to_underlying(m_bindingPoint) + 1u };
        }
        void tie(gl::handle_t indexBuffer , gl::count_t indices)
        {
            gl::vertex_array_element_buffer(m_handle, indexBuffer);
            m_indexCount = indices;
        }

        void set_attribute_divisor(gl::binding_t binding, gl::uint32_t divisor)
        {
            gl::vertex_array_binding_divisor(m_handle, binding, divisor);
        }

        auto index_count() const
        {
            return m_indexCount;
        }

        VertexArray& operator=(VertexArray&&) noexcept = default;

    private:
        gl::index_t   m_attributeIndex{};
        gl::binding_t m_bindingPoint{};
        gl::count_t   m_indexCount{};
    };
}
