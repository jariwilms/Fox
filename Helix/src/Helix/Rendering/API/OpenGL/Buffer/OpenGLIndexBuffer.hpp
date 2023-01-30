#pragma once

#include "stdafx.hpp"

#include "OpenGLBuffer.hpp"

namespace hlx
{
    class OpenGLIndexBuffer : public OpenGLBuffer<unsigned int>
    {
    public:
        OpenGLIndexBuffer(unsigned int count)
            : Buffer{ count }, OpenGLBuffer{ GL_ELEMENT_ARRAY_BUFFER, count } {}
        OpenGLIndexBuffer(std::span<const unsigned int> data)
            : Buffer{ static_cast<unsigned int>(data.size()) }, OpenGLBuffer{ GL_ELEMENT_ARRAY_BUFFER, data } {}
        ~OpenGLIndexBuffer() = default;
    };
}
