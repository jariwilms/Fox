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

            //SSBO, 
            //TransformFeedback, 
            
            //DrawIndirect?, 
            //PixelPack?, 
            //PixelUnpack?, 
            //Texture?, 
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

        Buffer(Buffer&& other) noexcept
        {
            m_size = std::exchange(other.m_size, fox::size_t{ 0u });
        }

        fox::size_t size() const
        {
            return m_size;
        }

        Buffer& operator=(Buffer&& other) noexcept
        {
            if (this != &other)
            {
                m_size = std::exchange(other.m_size, m_size);
            }

            return *this;
        }

    protected:
        Buffer(fox::size_t size)
            : m_size{ size } {}

        fox::size_t m_size{};
    };
}
