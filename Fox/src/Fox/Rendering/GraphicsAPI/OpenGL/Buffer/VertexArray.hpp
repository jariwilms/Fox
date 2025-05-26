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

        void set_attribute_divisor(gl::index_t index, gl::uint32_t divisor)
        {
            gl::vertex_array_binding_divisor(m_handle, index, divisor);
        }
        
        template<typename T>
        void tie(std::shared_ptr<gl::Buffer<T>> vertexBuffer, VertexLayout layout)
        {
            gl::vertex_array_vertex_buffer(m_handle, vertexBuffer->handle(), m_bindingPoint, static_cast<gl::size_t>(layout.stride()), gl::index_t{ 0u });

            gl::offset_t offset{};
            for (const auto& attribute : layout.attributes())
            {
                enable_attribute(m_attributeIndex);

                gl::vertex_array_attribute_format (m_handle, m_attributeIndex, offset, gl::map_data_type(attribute.dataType), attribute.count, attribute.isNormalized);
                gl::vertex_array_attribute_binding(m_handle, m_attributeIndex, m_bindingPoint);
                if (attribute.isStatic) set_attribute_divisor(m_attributeIndex, attribute.divisionRate);

                offset += static_cast<gl::offset_t>(attribute.stride());

                m_attributeIndexToBufferMap.emplace(m_attributeIndex, vertexBuffer->handle());
                ++m_attributeIndex;
            }

            m_bindingPointToBufferMap.emplace(m_bindingPoint, vertexBuffer->handle());
            ++m_bindingPoint;
        }
        void tie(std::shared_ptr<gl::Buffer<gl::uint32_t>> indexBuffer)
        {
            gl::vertex_array_element_buffer(m_handle, indexBuffer->handle());

            m_indexBuffer = indexBuffer;
        }

        gl::count_t index_count() const
        {
            return m_indexBuffer->count();
        }

        const std::unordered_map<gl::uint32_t, gl::handle_t>& binding_points() const
        {
            return m_bindingPointToBufferMap;
        }
        const std::unordered_map<gl::uint32_t, gl::handle_t>& attributes()     const
        {
            return m_attributeIndexToBufferMap;
        }

        VertexArray& operator=(VertexArray&&) noexcept = default;

    private:
        gl::index_t m_attributeIndex{};
        gl::index_t m_bindingPoint{};

        std::unordered_map<gl::uint32_t, gl::handle_t> m_bindingPointToBufferMap{};
        std::unordered_map<gl::uint32_t, gl::handle_t> m_attributeIndexToBufferMap{};

        std::shared_ptr<gl::Buffer<gl::uint32_t>> m_indexBuffer{};
    };
}
