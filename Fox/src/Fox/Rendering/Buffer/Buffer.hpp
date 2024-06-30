#pragma once

#include "stdafx.hpp"

namespace hlx::gfx::api
{
    class Buffer
    {
    public:
        enum class Type
        {
            Vertex,
            Index,

            Uniform,
            UniformArray, 
        };
        enum class Access
        {
            Static,
            Dynamic,
        };
        enum class Mapping
        {
            Read, 
            Write, 
            ReadWrite, 
        };

        size_t size() const
        {
            return m_size;
        }

    protected:
        Buffer(size_t size)
            : m_size{ size } {}

        size_t m_size{};
    };
}
