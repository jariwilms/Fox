#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/Buffer/Buffer.hpp"
#include "Fox/Rendering/Layout/VertexLayout.hpp"

namespace fox::gfx::api::gl
{
    class VertexArray : public gl::Object
    {
    public:
        VertexArray()
        {
            m_handle = gl::create_vertex_array();
        }
        ~VertexArray()
        {
            gl::delete_vertex_array(m_handle);
        }

        void bind()
        {
            gl::bind_vertex_array(m_handle);
        }

        void enable_attribute(gl::uint32_t index)
        {
            gl::enable_vertex_array_attribute(m_handle, index);
        }
        void disable_attribute(gl::uint32_t index)
        {
            gl::disable_vertex_array_attribute(m_handle, index);
        }

        void set_attribute_divisor(gl::uint32_t attribute, gl::uint32_t divisor)
        {
            gl::vertex_array_binding_divisor(m_handle, attribute, divisor);
        }

        void tie(std::shared_ptr<const gl::BufferObject<api::Buffer::Type::Vertex>> buffer, VertexLayout layout)
        {
            gl::vertex_array_vertex_buffer(m_handle, buffer->handle(), m_bindingPoint, static_cast<gl::size_t>(layout.stride()));

            gl::uint32_t offset{};
            for (const auto& attribute : layout.attributes())
            {
                enable_attribute(m_attributeIndex);

                gl::vertex_array_attribute_format(m_handle,  m_attributeIndex, offset, gl::map_data_type(attribute.dataType), attribute.count, attribute.isNormalized);
                gl::vertex_array_attribute_binding(m_handle, m_attributeIndex, m_bindingPoint);
                if (attribute.isStatic) set_attribute_divisor(m_attributeIndex, attribute.divisionRate);

                offset += static_cast<gl::uint32_t>(attribute.stride());

                m_attributeIndexToBufferMap.emplace(m_attributeIndex, buffer->handle());
                ++m_attributeIndex;
            }

            m_bindingPointToBufferMap.emplace(m_bindingPoint, buffer->handle());
            ++m_bindingPoint;
        }
        void tie(std::shared_ptr<const gl::StaticBuffer<api::Buffer::Type::Index, fox::uint32_t>> buffer)
        {
            gl::vertex_array_element_buffer(m_handle, buffer->handle());

            m_indexBuffer = buffer;
        }

        const std::unordered_map<gl::uint32_t, gl::handle_t>& binding_points() const
        {
            return m_bindingPointToBufferMap;
        }
        const std::unordered_map<gl::uint32_t, gl::handle_t>& attributes()     const
        {
            return m_attributeIndexToBufferMap;
        }

        fox::count_t index_count() const
        {
            return static_cast<fox::count_t>(m_indexBuffer->size() / sizeof(fox::uint32_t));
        }

    private:
        gl::uint32_t m_attributeIndex{};
        gl::uint32_t m_bindingPoint{};

        std::unordered_map<gl::uint32_t, gl::handle_t> m_bindingPointToBufferMap{};
        std::unordered_map<gl::uint32_t, gl::handle_t> m_attributeIndexToBufferMap{};

        std::shared_ptr<const gl::StaticBuffer<api::Buffer::Type::Index, gl::uint32_t>> m_indexBuffer{};
    };
}
