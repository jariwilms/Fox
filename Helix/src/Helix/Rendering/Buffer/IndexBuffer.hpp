#pragma once

#include "stdafx.hpp"

#include "Buffer.hpp"

namespace hlx
{
    class IndexBuffer : public Buffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void bind()     const = 0;
        virtual void unbind()   const = 0;
        virtual bool is_bound() const = 0;

        void copy(std::span<const unsigned int> data)
        {
            copy(data.size_bytes(), 0, static_cast<const void*>(data.data()));
        }
        template<typename T>
        void copy_range(unsigned int offset, std::span<const unsigned int> data)
        {
            copy(data.size_bytes(), offset * sizeof(unsigned int), static_cast<void*>(data.data()));
        }

        unsigned int count() const
        {
            return static_cast<unsigned int>(m_size / sizeof(unsigned int));
        }

    protected:
        IndexBuffer(unsigned int count)
            : Buffer{ count * sizeof(unsigned int) } {}

        virtual void copy(size_t size, size_t offset, const void* data) = 0;
    };
}
