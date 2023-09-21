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
            m_id = OpenGL::create_vertex_array();
        }
        ~OpenGLVertexArray()
        {
            OpenGL::delete_vertex_array(m_id);
        }

        void bind()     const override
        {
            OpenGL::bind_vertex_array(m_id);
        }

        void tie(const std::shared_ptr<VertexBuffer> vertexBuffer, const std::shared_ptr<VertexLayout> vertexLayout) override
        {
            if (m_bindingIndex == 16) throw std::runtime_error{ "BindingIndex may not exceed 16!" };

            const auto& glBuffer = std::static_pointer_cast<OpenGLVertexBuffer>(vertexBuffer);
            OpenGL::vertex_array_vertex_buffer(m_id, glBuffer->id(), m_bindingIndex, static_cast<GLsizei>(vertexLayout->stride()));
            
            GLint offset{};
            for (const auto& attribute : vertexLayout->attributes())
            {
                const auto internalType = OpenGL::type_enum(attribute.hash());
                const auto typeSize = OpenGL::type_size(attribute.hash());

                OpenGL::enable_vertex_array_attribute(m_id, m_attributeIndex);
                OpenGL::vertex_array_attribute_format(m_id, m_attributeIndex, attribute.count(), internalType, offset, attribute.normalized());
                OpenGL::vertex_array_attribute_binding(m_id, m_attributeIndex, m_bindingIndex);

                offset += static_cast<GLint>(attribute.count() * typeSize);

                m_primitiveCount += static_cast<unsigned int>(vertexBuffer->size() / (static_cast<size_t>(attribute.count()) * typeSize));
                ++m_attributeIndex;
            }

            ++m_bindingIndex;
        }
        void tie(const std::shared_ptr<IndexBuffer>  indexBuffer)                                                    override
        {
            m_indexBuffer = std::static_pointer_cast<OpenGLIndexBuffer>(indexBuffer);
            OpenGL::vertex_array_element_buffer(m_id, m_indexBuffer->id());
        }

        unsigned int primitive_count() const override
        {
            return m_primitiveCount;
        }
        bool indexed() const override
        {
            return m_indexBuffer != nullptr;
        }

        const std::shared_ptr<const IndexBuffer> index_buffer() const override
        {
            return m_indexBuffer;
        }

        GLuint id() const
        {
            return m_id;
        }

    private:
        GLuint       m_id{};
        GLuint       m_attributeIndex{};
        unsigned int m_bindingIndex{};
        unsigned int m_primitiveCount{};

        std::shared_ptr<const OpenGLIndexBuffer> m_indexBuffer{};
    };
}
