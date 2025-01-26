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

            //DrawIndirect, 
            //PixelPack, 
            //PixelUnpack, 
            //ShaderStorage, 
            //Texture, 
            //TransformFeedback, 
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
        ~Buffer() = default;

        fox::size_t m_size{};
    };
}
