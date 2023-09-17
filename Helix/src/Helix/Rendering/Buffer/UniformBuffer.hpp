#pragma once

#include "stdafx.hpp"

#include "Buffer.hpp"

namespace hlx
{
    template<typename T>
    class UniformBuffer : public Buffer
    {
    public:
        virtual ~UniformBuffer() = default;

        void copy(const T& data)
        {
            copy(sizeof(T), 0, static_cast<const void*>(&data));
        }
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
            copy(result.size(), offset, static_cast<const void*>(result.data()));
        }

        virtual void bind(unsigned int binding) = 0;

    protected:
        UniformBuffer(unsigned int binding)
            : Buffer{ sizeof(T) }, m_binding{ binding } {}

        virtual void copy(size_t size, size_t offset, const void* data) = 0;

        unsigned int m_binding{};
    };
}
