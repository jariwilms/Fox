#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/Buffer/VertexArray.hpp"
#include "Fox/Rendering/API/Layout/VertexLayout.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Buffer/Buffer.hpp"

namespace fox::gfx::api::gl
{
    class VertexArray : public api::VertexArray, public gl::Object
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

        void tie(gl::handle_t vertexBuffer, VertexLayout layout)
        {
            gl::vertex_array_vertex_buffer(m_handle, vertexBuffer, m_bindingPoint, static_cast<gl::sizei_t>(layout.stride()), gl::offset_t{});

            gl::uint32_t offset{};
            for (const auto& attribute : layout.attributes())
            {
                enable_attribute(m_attributeIndex);

                gl::vertex_array_attribute_format(m_handle,  m_attributeIndex, offset, gl::map_data_type(attribute.dataType), attribute.count, attribute.isNormalized);
                gl::vertex_array_attribute_binding(m_handle, m_attributeIndex, m_bindingPoint);
                if (attribute.isStatic) set_attribute_divisor(m_attributeIndex, attribute.divisionRate);

                offset += static_cast<gl::uint32_t>(attribute.stride());

                m_attributeIndexToBufferMap.emplace(m_attributeIndex, vertexBuffer);
                ++m_attributeIndex;
            }

            m_bindingPointToBufferMap.emplace(m_bindingPoint, vertexBuffer);
            ++m_bindingPoint;
        }
        void tie(std::shared_ptr<gl::StaticBuffer<api::Buffer::Type::Index, gl::uint32_t>> indexBuffer)
        {
            gl::vertex_array_element_buffer(m_handle, indexBuffer->handle());

            m_indexBuffer = indexBuffer;
        }

        fox::count_t index_count() const
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
        gl::uint32_t m_attributeIndex{};
        gl::uint32_t m_bindingPoint{};

        std::unordered_map<gl::uint32_t, gl::handle_t> m_bindingPointToBufferMap{};
        std::unordered_map<gl::uint32_t, gl::handle_t> m_attributeIndexToBufferMap{};

        std::shared_ptr<gl::StaticBuffer<api::Buffer::Type::Index, gl::uint32_t>> m_indexBuffer{};
    };
}
