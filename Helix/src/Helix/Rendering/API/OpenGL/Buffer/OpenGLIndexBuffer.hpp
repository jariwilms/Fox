#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Buffer/IndexBuffer.hpp"

namespace hlx
{
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(unsigned int count)
            : IndexBuffer{ count }
        {
            m_internalTarget = GL_ELEMENT_ARRAY_BUFFER;

            glCreateBuffers(1, &m_internalId);
            glNamedBufferStorage(m_internalId, m_size, nullptr, GL_DYNAMIC_STORAGE_BIT);
        }
        OpenGLIndexBuffer(std::span<const unsigned int> data)
            : OpenGLIndexBuffer{ static_cast<unsigned int>(data.size()) }
        {
            IndexBuffer::copy(data);
        }
        ~OpenGLIndexBuffer() = default;

        void bind()     const override
        {
            glBindBuffer(m_internalTarget, m_internalId);
        }
        void unbind()   const override
        {
            glBindBuffer(m_internalTarget, 0);
        }
        bool is_bound() const override
        {
            throw std::runtime_error{ "Method has not been implemented!" };
        }

        GLuint internal_id()     const
        {
            return m_internalId;
        }
        GLenum internal_target() const
        {
            return m_internalTarget;
        }

    protected:
        void copy(size_t size, size_t offset, const void* data) override
        {
            if (size + offset > m_size) throw std::runtime_error{ "Data size exceeds buffer size!" };

            glNamedBufferSubData(m_internalId, offset, size, data);
        }

    private:
        GLuint m_internalId{};
        GLenum m_internalTarget{};
    };
}
