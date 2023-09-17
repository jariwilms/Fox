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
            glCreateVertexArrays(1, &m_internalId);
        }
        ~OpenGLVertexArray()
        {
            glDeleteVertexArrays(1, &m_internalId);
        }

        void bind()     const override
        {
            glBindVertexArray(m_internalId);
            s_boundVertexArrayId = m_internalId;
        }
        void unbind()   const override
        {
            if (s_boundVertexArrayId != m_internalId) return;

            glBindVertexArray(0);
        }
        bool is_bound() const override
        {
            return m_internalId == s_boundVertexArrayId;
        }

        void tie(const std::shared_ptr<VertexBuffer> vertices, const std::shared_ptr<VertexLayout> layout) override
        {
            if (m_bindingIndex == 16) throw std::runtime_error{ "BindingIndex may not exceed 16!" };

            const auto& glBuffer = std::static_pointer_cast<OpenGLVertexBuffer>(vertices);
            glVertexArrayVertexBuffer(m_internalId, m_bindingIndex, glBuffer->internal_id(), 0, static_cast<GLsizei>(layout->stride()));
            
            GLint offset{};
            for (const auto& attribute : layout->attributes())
            {
                const auto internalType = OpenGL::type_enum(attribute.hash());
                const auto typeSize = OpenGL::type_size(attribute.hash());

                glEnableVertexArrayAttrib(m_internalId, m_attributes);
                glVertexArrayAttribFormat(m_internalId, m_attributes, attribute.count(), internalType, attribute.is_normalized(), offset);
                glVertexArrayAttribBinding(m_internalId, m_attributes, m_bindingIndex);

                offset += static_cast<GLint>(attribute.count() * typeSize);
                ++m_attributes;
            }

            ++m_bindingIndex;
        }
        void tie(const std::shared_ptr<IndexBuffer> indices)                                               override
        {
            m_indices = indices;
            const auto& glIndices = std::static_pointer_cast<OpenGLIndexBuffer>(indices);

            glVertexArrayElementBuffer(m_internalId, glIndices->internal_id());
        }

        GLuint internal_id() const
        {
            return m_internalId;
        }

    private:
        GLuint       m_internalId{};
        unsigned int m_bindingIndex{};

        static inline GLuint s_boundVertexArrayId{};
    };
}
