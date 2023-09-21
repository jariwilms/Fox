#pragma once

#include "stdafx.hpp"

namespace hlx
{
    struct VertexAttribute
    {
    public:
        VertexAttribute(unsigned int count, t_hash tHash)
            : m_count{ count }, m_tHash{ tHash } {}

        unsigned int count() const
        {
            return m_count;
        }
        bool normalized() const
        {
            return m_normalized;
        }

        t_hash hash() const
        {
            return m_tHash;
        }

    private:
        unsigned int m_count{};
        bool m_normalized{};

        t_hash m_tHash{};
    };
}
