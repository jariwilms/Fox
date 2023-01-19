#pragma once

#include "stdafx.hpp"

namespace hlx
{
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
}
