#pragma once

#include "stdafx.hpp"

namespace hlx
{
    template<typename T>
    class UniformBuffer : public virtual Buffer<T>
    {
    public:
        virtual ~UniformBuffer() = default;

        virtual void copy(const T& data) = 0;
        template<typename... U>
        void copy_tuple(size_t offset, const std::tuple<U...>& data)
        {
            std::array<byte, sizeof(std::tuple<U...>)> result{};

            const auto convert_byte_array = [&](auto&&... args)
            {
                size_t size{};
                ((std::memcpy(result.data() + size, &args, sizeof(args)), size += sizeof(args)), ...);
            };

            std::apply(convert_byte_array, data);
            copy_range(result.size(), offset, result.data());
        }

        virtual void bind_base(unsigned int index) = 0;
        virtual void bind_range(unsigned int index, size_t size, size_t offset) = 0;

    protected:
        UniformBuffer(unsigned int count)
            : Buffer<T>{ count } {}

        virtual void copy_range(size_t size, size_t offset, const void* data) = 0;
    };
}
