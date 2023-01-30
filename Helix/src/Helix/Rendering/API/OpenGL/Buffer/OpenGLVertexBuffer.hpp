#pragma once

#include "stdafx.hpp"

#include "OpenGLBuffer.hpp"

namespace hlx
{
    template<typename T>
    class OpenGLVertexBuffer : public virtual OpenGLBuffer<T>
    {
    public:
        OpenGLVertexBuffer(unsigned int count)
            : Buffer<T>{ count }, OpenGLBuffer<T>{ GL_ARRAY_BUFFER, count } {}
        OpenGLVertexBuffer(std::span<const T> data)
            : Buffer<T>{ static_cast<unsigned int>(data.size()) }, OpenGLBuffer<T>{ GL_ARRAY_BUFFER, data } {}
        ~OpenGLVertexBuffer() = default;
    };
}
