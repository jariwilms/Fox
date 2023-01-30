#pragma once

#include "stdafx.hpp"

#include "Buffer.hpp"

namespace hlx
{
    template<typename T>
    class UniformArrayBuffer : public virtual Buffer<T>
    {
    public:
        virtual ~UniformArrayBuffer() = default;

        virtual void copy(std::span<const T> data) = 0;
        virtual void copy_index(unsigned int index, const T& data) = 0;
        virtual void copy_index_range(unsigned int index, std::span<const T> data) = 0;

        virtual void bind_base(unsigned int binding) = 0;
        virtual void bind_range(unsigned int count, unsigned int binding, unsigned int index, size_t offset) = 0;

    protected:
        UniformArrayBuffer(unsigned int count, unsigned int binding)
            : Buffer<T>{ count }, m_binding{ binding } {}

        virtual void copy_range(size_t size, size_t offset, const void* data) = 0;

        unsigned int m_binding{};
    };
}
