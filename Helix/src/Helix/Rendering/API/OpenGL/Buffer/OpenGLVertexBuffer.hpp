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
            : OpenGLBuffer<T>{ GL_ARRAY_BUFFER, count }, Buffer<T>{ count } {}
        OpenGLVertexBuffer(std::span<const T> data)
            : OpenGLBuffer<T>{ GL_ARRAY_BUFFER, data }, Buffer<T>{ static_cast<unsigned int>(data.size()) } {}
        ~OpenGLVertexBuffer() = default;
    };
}
