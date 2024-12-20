#pragma once

#include "stdafx.hpp"

namespace fox::gfx::api
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

        fox::size_t size() const
        {
            return m_size;
        }

    protected:
        Buffer(fox::size_t size)
            : m_size{ size } {}

        fox::size_t m_size{};
    };
}
