#pragma once

#include "stdafx.hpp"

namespace hlx
{
    class Buffer
    {
    public:
        virtual ~Buffer() = default;

        size_t size()  const
        {
            return m_size;
        }

    protected:
        Buffer(size_t size)
            : m_size{ size } {}

        size_t m_size{};
    };
}
