#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Buffer/VertexContainer.hpp"
#include "Helix/Core/Library/Semantics/NonCopyable.hpp"

namespace hlx
{
    class UniformBuffer : public IBindable, public NonCopyable
    {
    public:
        virtual ~UniformBuffer() = default;

        virtual void bind_base(unsigned int index) = 0;
        virtual void bind_range(unsigned int index, size_t size, size_t offset) = 0;

        template<typename T>
        void copy(const T& data)
        {
            _copy(sizeof(T), 0, &data);
        }
        template<typename... T>
        void copy_range(size_t offset, const std::tuple<T...>& data)
        {
            _copy(sizeof(std::tuple<T...>), offset, &data);
        }

    protected:
        UniformBuffer(size_t size)
            : m_size{ size } {}

        virtual void _copy(size_t size, size_t offset, const void* data) = 0;

        Id m_id{};
        size_t m_size{};
    };
}
