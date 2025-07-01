#pragma once

#include <stdafx.hpp>

#include <fox/rendering/api/opengl/buffer/buffer.hpp>
#include <fox/rendering/layout/vertex_layout.hpp>

namespace fox::gfx::api::gl
{
    class VertexArray : public gl::Object
    {
    public:
        VertexArray()
        {
            handle_ = gl::create_vertex_array();
        }
        VertexArray(VertexArray&&) noexcept = default;
        ~VertexArray()
        {
            gl::delete_vertex_array(handle_);
        }

        void bind()
        {
            gl::bind_vertex_array(handle_);
        }

        void enable_attribute (gl::index_t index)
        {
            gl::enable_vertex_array_attribute(handle_, index);
        }
        void disable_attribute(gl::index_t index)
        {
            gl::disable_vertex_array_attribute(handle_, index);
        }

        void tie(gl::handle_t vertexBuffer, const gfx::VertexLayout& layout)
        {
            gl::vertex_array_vertex_buffer(handle_, vertexBuffer, bindingPoint_, static_cast<gl::size_t>(layout.stride()), gl::index_t{ 0u });

            gl::offset_t offset{};
            for (const auto& attribute : layout.attributes())
            {
                enable_attribute(attributeIndex_);

                gl::vertex_array_attribute_format (handle_, attributeIndex_, offset, gl::map_type(attribute.type), attribute.count, attribute.isNormalized);
                gl::vertex_array_attribute_binding(handle_, attributeIndex_, bindingPoint_);
                if (attribute.isStatic) set_attribute_divisor(static_cast<gl::binding_t>(attributeIndex_), attribute.divisionRate);

                offset += static_cast<gl::offset_t>(attribute.count * attribute.size);
                ++attributeIndex_;
            }

            bindingPoint_ = gl::binding_t{ gl::to_underlying(bindingPoint_) + 1u };
        }
        void tie(gl::handle_t indexBuffer , gl::count_t indices)
        {
            gl::vertex_array_element_buffer(handle_, indexBuffer);
            indexCount_ = indices;
        }

        void set_attribute_divisor(gl::binding_t binding, gl::uint32_t divisor)
        {
            gl::vertex_array_binding_divisor(handle_, binding, divisor);
        }

        auto index_count() const
        {
            return indexCount_;
        }

        VertexArray& operator=(VertexArray&&) noexcept = default;

    private:
        gl::index_t   attributeIndex_{};
        gl::binding_t bindingPoint_{};
        gl::count_t   indexCount_{};
    };
}
