#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Buffer/VertexArray.hpp"

namespace hlx
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray()
        {
            glCreateVertexArrays(1, &m_id);
        }
        ~OpenGLVertexArray()
        {
            glDeleteVertexArrays(1, &m_id);
        }

        void bind() const override
        {
            glBindVertexArray(m_id);
        }
        void unbind() const override
        {
            glBindVertexArray(0);
        }
        bool bound() const override
        {
            return false;
        }

        void tie(Id bufferId, const std::shared_ptr<VertexLayout> colorDepth) override
        {
            static int bindingIndex{};

            glVertexArrayVertexBuffer(m_id, bindingIndex, bufferId, 0, static_cast<GLsizei>(colorDepth->stride()));
            
            GLint offset{};
            for (const auto& attribute : colorDepth->attributes())
            {
                const auto internalType = OpenGL::type_enum(attribute.hash());
                const auto typeSize = OpenGL::type_size(attribute.hash());

                glEnableVertexArrayAttrib(m_id, m_attributes);
                glVertexArrayAttribFormat(m_id, m_attributes, attribute.count(), internalType, attribute.is_normalized(), offset);
                glVertexArrayAttribBinding(m_id, m_attributes, bindingIndex);

                offset += static_cast<GLint>(attribute.count() * typeSize);
                ++m_attributes;
            }

            ++bindingIndex;
        }
        void tie(const std::shared_ptr<IndexBuffer> indices) override
        {
            m_indices = indices;
            glVertexArrayElementBuffer(m_id, m_indices->id());
        }
    };
}
