#pragma once

#include "stdafx.hpp"

#include "Buffer.hpp"

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
                ((std::memcpy(result.data() + size, &args, sizeof(args)), size += sizeof(args)), ...); //fold expression
            };

            std::apply(convert_byte_array, data);
            copy_range(result.size(), offset, result.data());
        }

        virtual void bind_base(unsigned int binding) = 0;
        virtual void bind_range(unsigned int binding, size_t size, size_t offset) = 0;

    protected:
        UniformBuffer(unsigned int binding)
            : Buffer<T>{ 1 }, m_binding{ binding } {}

        virtual void copy_range(size_t size, size_t offset, const void* data) = 0;

        unsigned int m_binding{};
    };
}
