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
    template<typename T>
    class Buffer : public IBindable
    {
    public:
        virtual ~Buffer() = default;

        void copy(const std::span<T>& data)
        {
            const auto dataSize = data.size() * sizeof(T);

            if (data.size() * sizeof(T) != m_size) throw std::range_error{ "Data size is not equal to buffer size!" };

            copy_base(data.data());
        }
        void copy_range(unsigned int offset, const std::span<T>& data)
        {
            const auto dataSize = data.size() * sizeof(T);
            const auto offsetSize = offset * sizeof(T);

            if (dataSize + offsetSize > m_size) throw std::range_error{ "Data size is greater than buffer range!" };

            copy_range(dataSize, offsetSize, data.data());
        }

        size_t size() const
        {
            return m_size;
        }

    protected:
        Buffer(unsigned int count)
            : m_size{ count * sizeof(T) } {}

        virtual void copy(const void* data) = 0;
        virtual void copy_range(size_t size, size_t offset, const void* data) = 0;

        size_t m_size{};
    };
    template<typename T>
    class UniformBuffer : public virtual Buffer<T>
    {
    public:
        virtual ~UniformBuffer() = default;

        void copy(const T& data)
        {
            Buffer<T>::copy(&data);
        }
        template<typename... T>
        void copy_range(size_t offset, const std::tuple<T...>& data)
        {
            Buffer<T>::copy_range(sizeof(std::tuple<T...>), offset, &data);
        }

        virtual void bind_base(unsigned int index) = 0;
        virtual void bind_range(unsigned int index, size_t size, size_t offset) = 0;

    protected:
        UniformBuffer(unsigned int count)
            : Buffer<T>{ count } {}
    };

    class VertexArray : public IBindable
    {
    public:
        virtual ~VertexArray() = default;

        template<typename T>
        void tie(const std::shared_ptr<Buffer<T>> vertices, const std::shared_ptr<VertexLayout> layout)
        {
            tie(vertices->id());
        }
        virtual void tie(const std::shared_ptr<IndexBuffer> indices) = 0;

    protected:
        VertexArray() = default;

        virtual void tie(Id bufferId, const std::shared_ptr<VertexLayout> layout) = 0;

        unsigned int m_attributes{};
    };

#include "glad/glad.h"
#include "glfw/glfw3.h"

    template<typename T>
    class OpenGLBuffer : public virtual Buffer<T>
    {
    public:
        OpenGLBuffer(GLenum target, unsigned int count)
            : Buffer<T>{ count }, m_internalTarget{ target }
        {
            glCreateBuffers(1, &m_id);
            glNamedBufferStorage(m_id, m_size, nullptr, GL_DYNAMIC_STORAGE_BIT);
        }
        OpenGLBuffer(GLenum target, const std::span<T>& data) 
            : Buffer<T>{ static_cast<unsigned int>(data.size()) }, m_internalTarget{ target }
        {
            glCreateBuffers(1, &m_id);
            glNamedBufferStorage(m_id, m_size, data.data(), GL_DYNAMIC_STORAGE_BIT);
        }
        virtual ~OpenGLBuffer()
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
        using Buffer<T>::m_size;

        void copy(const void* data) override
        {
            glNamedBufferSubData(m_id, 0, m_size, data);
        }
        void copy_range(size_t size, size_t offset, const void* data) override
        {
            glNamedBufferSubData(m_id, offset, size, data);
        }

        GLenum m_internalTarget{};
    };

    template<typename T>
    class OpenGLVertexBuffer : public virtual OpenGLBuffer<T>
    {
    public:
        OpenGLVertexBuffer(unsigned int count)
            : OpenGLBuffer<T>{ GL_ARRAY_BUFFER, count }, Buffer<T>{ count } {}
        OpenGLVertexBuffer(const std::span<unsigned int>& data)
            : OpenGLBuffer<T>{ GL_ARRAY_BUFFER, data }, Buffer<T>{ static_cast<unsigned int>(data.size()) } {}
        ~OpenGLVertexBuffer() = default;

    protected:
        using OpenGLBuffer<T>::m_internalTarget;
    };
    class OpenGLIndexBuffer : public OpenGLBuffer<unsigned int>
    {
    public:
        OpenGLIndexBuffer(unsigned int count)
            : OpenGLBuffer{ GL_ELEMENT_ARRAY_BUFFER, count }, Buffer{ count } {}
        OpenGLIndexBuffer(const std::span<unsigned int>& data)
            : OpenGLBuffer{ GL_ELEMENT_ARRAY_BUFFER, data }, Buffer{ static_cast<unsigned int>(data.size()) } {}
        ~OpenGLIndexBuffer() = default;
    };
    template<typename T>
    class OpenGLUniformBuffer : public OpenGLBuffer<T>, public UniformBuffer<T>
    {
    public:
        OpenGLUniformBuffer(unsigned int count) 
            : OpenGLBuffer<T>{ GL_UNIFORM_BUFFER, count }, UniformBuffer<T>{ count }, Buffer<T>{ count } {}
        OpenGLUniformBuffer(const std::span<T>& data)
            : OpenGLBuffer<T>{ GL_UNIFORM_BUFFER, data }, UniformBuffer<T>{ static_cast<unsigned int>(data.size()) }, Buffer<T>{ static_cast<unsigned int>(data.size()) } {}
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
        using OpenGLBuffer<T>::m_internalTarget;
    };

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray()
        {
            glCreateVertexArrays(1, &m_id);
        }

        void bind() override
        {
            glBindVertexArray(m_id);
        }
        void unbind() override
        {
            glBindVertexArray(0);
        }
        bool is_bound() override
        {
            return false;
        }

        void tie(Id bufferId, const std::shared_ptr<VertexLayout> layout) override
        {
            static int bindingIndex{};

            glVertexArrayVertexBuffer(m_id, bindingIndex, bufferId, 0, static_cast<GLsizei>(layout->stride()));

            GLint offset{};
            for (const auto& attribute : layout->attributes())
            {
                glEnableVertexArrayAttrib(m_id, m_attributes);
                glVertexArrayAttribFormat(m_id, m_attributes, attribute.count, attribute.internalType, attribute.isNormalized, offset);
                glVertexArrayAttribBinding(m_id, m_attributes, bindingIndex);

                offset += static_cast<GLint>(attribute.count * attribute.tSize);
                ++m_attributes;
            }

            ++bindingIndex;
        }
        void tie(const std::shared_ptr<IndexBuffer> indices) override
        {
            glVertexArrayElementBuffer(m_id, indices->id());
        }
    };




    template<typename T>
    using VertexBuffer = Buffer<T>;
    using IndexBuffer = Buffer<unsigned int>;

    template<typename T>
    std::shared_ptr<VertexBuffer<T>> create_vbo(unsigned int count)
    {
        return std::make_shared<OpenGLVertexBuffer<T>>(count);
    }
    std::shared_ptr<IndexBuffer> create_ibo(unsigned int count)
    {
        return std::make_shared<OpenGLIndexBuffer>(count);
    }
    template<typename T>
    std::shared_ptr<UniformBuffer<T>> create_ubo(unsigned int count = 1)
    {
        return std::make_shared<OpenGLUniformBuffer<T>>(count);
    }

    void test()
    {
        struct TestStruct
        {
            int a{};
            float b{};
        };

        TestStruct ts;

        auto vbo = create_vbo<float>(12);
        auto ibo = create_ibo(12);
        auto ubo = create_ubo<TestStruct>(12);
    }
}
