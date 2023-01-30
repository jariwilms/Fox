#pragma once

#include "stdafx.hpp"

#include "OpenGLBuffer.hpp"

namespace hlx
{
    class OpenGLIndexBuffer : public OpenGLBuffer<unsigned int>
    {
    public:
        OpenGLIndexBuffer(unsigned int count)
            : OpenGLBuffer{ GL_ELEMENT_ARRAY_BUFFER, count }, Buffer{ count } {}
        OpenGLIndexBuffer(std::span<const unsigned int> data)
            : OpenGLBuffer{ GL_ELEMENT_ARRAY_BUFFER, data }, Buffer{ static_cast<unsigned int>(data.size()) } {}
        ~OpenGLIndexBuffer() = default;
    };
}
