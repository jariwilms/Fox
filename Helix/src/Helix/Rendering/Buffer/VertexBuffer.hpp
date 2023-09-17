#pragma once

#include "stdafx.hpp"

#include "Buffer.hpp"

namespace hlx
{
    class VertexBuffer : public Buffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void bind()     const = 0;
        virtual void unbind()   const = 0;
        virtual bool is_bound() const = 0;

        template<typename T>
        void copy(std::span<const T> data)
        {
            copy(data.size_bytes(), 0, static_cast<const void*>(data.data()));
        }
        template<typename T>
        void copy_range(unsigned int offset, std::span<const T> data)
        {
            copy(data.size_bytes(), offset * sizeof(T), static_cast<const void*>(data.data()));
        }

    protected:
        VertexBuffer(size_t size)
            : Buffer{ size } {}

        virtual void copy(size_t size, size_t offset, const void* data) = 0;
    };
}
