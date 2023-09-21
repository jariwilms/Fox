#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Buffer/VertexArray.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLVertexBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLIndexBuffer.hpp"

namespace hlx
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray()
        {
            m_internalId = OpenGL::create_vertex_array();
        }
        ~OpenGLVertexArray()
        {
            OpenGL::delete_vertex_array(m_internalId);
        }

        void bind()     const override
        {
            OpenGL::bind_vertex_array(m_internalId);
        }

        void tie(const std::shared_ptr<VertexBuffer> vertices, const std::shared_ptr<VertexLayout> layout) override
        {
            if (m_bindingIndex == 16) throw std::runtime_error{ "BindingIndex may not exceed 16!" };

            const auto& glBuffer = std::static_pointer_cast<OpenGLVertexBuffer>(vertices);
            OpenGL::vertex_array_vertex_buffer(m_internalId, glBuffer->internal_id(), m_bindingIndex, static_cast<GLsizei>(layout->stride()));
            
            GLint offset{};
            for (const auto& attribute : layout->attributes())
            {
                const auto internalType = OpenGL::type_enum(attribute.hash());
                const auto typeSize = OpenGL::type_size(attribute.hash());

                OpenGL::enable_vertex_array_attribute(m_internalId, m_attributeIndex);
                OpenGL::vertex_array_attribute_format(m_internalId, m_attributeIndex, attribute.count(), internalType, offset, attribute.is_normalized());
                OpenGL::vertex_array_attribute_binding(m_internalId, m_attributeIndex, m_bindingIndex);

                offset += static_cast<GLint>(attribute.count() * typeSize);
                ++m_attributeIndex;
            }

            ++m_bindingIndex;
        }
        void tie(const std::shared_ptr<IndexBuffer> indices)                                               override
        {
            const auto& glIndexBuffer = std::static_pointer_cast<OpenGLIndexBuffer>(indices);
            OpenGL::vertex_array_element_buffer(m_internalId, glIndexBuffer->internal_id());

            m_indices = indices;
        }

        GLuint internal_id() const
        {
            return m_internalId;
        }

    private:
        GLuint       m_internalId{};
        GLuint       m_attributeIndex{};
        unsigned int m_bindingIndex{};
    };
}
