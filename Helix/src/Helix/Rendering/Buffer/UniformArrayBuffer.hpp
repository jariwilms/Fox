#pragma once

#include "stdafx.hpp"

#include "Buffer.hpp"

namespace hlx
{
    template<typename T>
    class UniformArrayBuffer : public Buffer
    {
    public:
        virtual ~UniformArrayBuffer() = default;

        virtual void bind(unsigned int binding) = 0;
        virtual void bind_range(unsigned int binding, unsigned int index, unsigned int count) = 0;

        void copy(std::span<const T> data)
        {
            copy(data.size_bytes(), 0, static_cast<const void*>(data.data()));
        }
        void copy_index(unsigned int index, const T& data)
        {
            copy(sizeof(T), index * sizeof(T), static_cast<const void*>(&data));
        }

    protected:
        UniformArrayBuffer(unsigned int binding, unsigned int count)
            : Buffer{ count * sizeof(T) }, m_binding{ binding } {}

        virtual void copy(size_t size, size_t offset, const void* data) = 0;

        unsigned int m_binding{};
    };
}
