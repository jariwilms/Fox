#pragma once

#include "stdafx.hpp"

namespace hlx::exp
{
    class IBindable
    {
    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual bool is_bound() = 0;

        Id id() const
        {
            return m_id;
        }

    protected:
        Id m_id{};
    };
    class BufferObject : public IBindable
    {
    public:
        virtual ~BufferObject() = default;

        size_t size() const
        {
            return m_size;
        }

    protected:
        BufferObject(size_t size)
            : m_size{ size } {}

        size_t m_size{};
    };

    template<typename T>
    class VertexBuffer : public BufferObject
    {
    public:
        virtual ~VertexBuffer() = default;

        void copy(const std::span<T>& data)
        {
            const auto dataSize = data.size() * sizeof(T);

            if (data.size() * sizeof(T) != m_size) throw std::range_error{ "Data size is greater than buffer size!" };

            copy(data.data());
        }
        void copy_range(unsigned int offset, const std::span<T>& data)
        {
            const auto dataSize = data.size() * sizeof(T);
            const auto offsetSize = offset * sizeof(T);

            if (dataSize + offsetSize > m_size) throw std::range_error{ "Data size is greater than buffer size!" };

            copy_range(dataSize, offsetSize, data.data());
        }

    protected:
        virtual void copy(const void* data) = 0;
        virtual void copy_range(size_t size, size_t offset, const void* data) = 0;

        VertexBuffer(unsigned int count)
            : BufferObject{ count * sizeof(T) }
        {
            std::cout << "vbuffer called\n";
        }
    };
    template<typename T>
    class UniformBuffer : public virtual VertexBuffer<T>
    {
    public:
        virtual ~UniformBuffer() = default;

        virtual void bind_base(unsigned int index) = 0;
        virtual void bind_range(unsigned int index, size_t size, size_t offset) = 0;

    protected:
        UniformBuffer(unsigned int count)
            : VertexBuffer<T>{ count } {}
    };

#include "glad/glad.h"
#include "glfw/glfw3.h"

    template<typename T>
    class OpenGLVertexBuffer : public virtual VertexBuffer<T>
    {
    public:
        OpenGLVertexBuffer(GLenum target, unsigned int count) 
            : VertexBuffer<T>{ count }, m_internalTarget{ target }
        {
            glCreateBuffers(1, &m_id);
            glNamedBufferStorage(m_id, m_size, nullptr, GL_DYNAMIC_STORAGE_BIT);
        }
        OpenGLVertexBuffer(GLenum target, const std::span<T>& data) 
            : VertexBuffer<T>{ static_cast<unsigned int>(data.size()) }, m_internalTarget{ target }
        {
            glCreateBuffers(1, &m_id);
            glNamedBufferStorage(m_id, m_size, data.data(), GL_DYNAMIC_STORAGE_BIT);
        }
        virtual ~OpenGLVertexBuffer()
        {
            glDeleteBuffers(1, &m_id);
        }

        void bind() override
        {
            glBindBuffer(m_internalTarget, m_id);
        }
        void unbind() override
        {
            glBindBuffer(m_internalTarget, 0);
        }
        bool is_bound() override
        {
            return false;
        }

    protected:
        using IBindable::m_id;
        using BufferObject::m_size;

        void copy(const void* data) override
        {
            glNamedBufferSubData(m_id, 0, m_size, data);
        }
        void copy_range(size_t size, size_t offset, const void* data) override
        {
            glNamedBufferSubData(m_id, offset, size, data);
        }

        GLenum m_internalTarget{ GL_VERTEX_ARRAY };
    };
    class OpenGLIndexBuffer : public OpenGLVertexBuffer<unsigned int>
    {
    public:
        OpenGLIndexBuffer(unsigned int count)
            : OpenGLVertexBuffer{ GL_ELEMENT_ARRAY_BUFFER, count }, VertexBuffer{ count } {}
        OpenGLIndexBuffer(const std::span<unsigned int>& data)
            : OpenGLVertexBuffer{ GL_ELEMENT_ARRAY_BUFFER, data }, VertexBuffer{ static_cast<unsigned int>(data.size()) } {}
        ~OpenGLIndexBuffer() = default;

    protected:
        using OpenGLVertexBuffer<unsigned int>::m_internalTarget;
    };
    template<typename T>
    class OpenGLUniformBuffer : public OpenGLVertexBuffer<T>, public UniformBuffer<T>
    {
    public:
        OpenGLUniformBuffer(unsigned int count) 
            : OpenGLVertexBuffer<T>{ GL_UNIFORM_BUFFER, count }, UniformBuffer<T>{ count }, VertexBuffer<T>{ count } {}
        OpenGLUniformBuffer(const std::span<T>& data)
            : OpenGLVertexBuffer<T>{ GL_UNIFORM_BUFFER, data }, UniformBuffer<T>{ static_cast<unsigned int>(data.size()) }, VertexBuffer<T>{ static_cast<unsigned int>(data.size()) } {}
        ~OpenGLUniformBuffer() = default;

        void bind_base(unsigned int index) override
        {
            glBindBufferBase(m_internalTarget, index, m_id);
        }
        void bind_range(unsigned int index, size_t size, size_t offset) override
        {
            glBindBufferRange(m_internalTarget, index, m_id, offset, size);
        }

    protected:
        using IBindable::m_id;
        using BufferObject::m_size;
        using OpenGLVertexBuffer<T>::m_internalTarget;
    };

    template<typename T>
    std::shared_ptr<VertexBuffer<T>> create_vbo(unsigned int count)
    {
        return std::make_shared<OpenGLVertexBuffer<T>>(GL_ARRAY_BUFFER, count);
    }
    using IndexBuffer = VertexBuffer<unsigned int>;
    std::shared_ptr<IndexBuffer> create_ibo(unsigned int count)
    {
        return std::make_shared<OpenGLIndexBuffer>(count);
    }

    void test()
    {
        struct TestStruct
        {
            int a{};
            float b{};
        };

        auto vbo = create_vbo<float>(12);
        auto ibo = create_ibo(12);
        //auto ubo = create_ubo<float>(12);

        OpenGLUniformBuffer<float> ub{12};
    }
}
