#pragma once

#include "stdafx.hpp"

namespace hlx
{
    struct VertexAttribute
    {
    public:
        VertexAttribute(unsigned int count, size_t tHash)
            : m_count{ count }, m_tHash{ tHash } {}

        unsigned int count() const
        {
            return m_count;
        }
        size_t hash() const
        {
            return m_tHash;
        }
        bool normalized() const
        {
            return m_normalized;
        }

    private:
        const unsigned int m_count{};
        const size_t m_tHash{};
        bool m_normalized{};
    };
}
