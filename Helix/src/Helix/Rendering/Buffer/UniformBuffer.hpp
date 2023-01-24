#pragma once

#include "stdafx.hpp"

namespace hlx
{
    template<typename T>
    class UniformBuffer : public virtual Buffer<T>
    {
    public:
        virtual ~UniformBuffer() = default;

        virtual void copy_all(const T& data) = 0;
        template<typename... U>
        void copy_tuple(size_t offset, const std::tuple<U...>& data)
        {
             //Buffer<T>::copy_range_void(sizeof(std::tuple<U...>), offset, &data);
        }

        virtual void bind_base(unsigned int index) = 0;
        virtual void bind_range(unsigned int index, size_t size, size_t offset) = 0;

    protected:
        UniformBuffer(unsigned int count)
            : Buffer<T>{ count } {}
    };
}
