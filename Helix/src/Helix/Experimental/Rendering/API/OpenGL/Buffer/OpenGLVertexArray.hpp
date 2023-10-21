#pragma once

#include "Helix/Experimental/Rendering/Buffer/VertexArray.hpp"
#include "OpenGLBuffer.hpp"

namespace hlx::gfx::imp
{
    template<>
    class GVertexArray<GraphicsAPI::OpenGL>
    {
    public:
        GVertexArray()
        {

        }

        template<typename T>
        void tie(const GBuffer<GraphicsAPI::OpenGL, Buffer::Type::Vertex, T>& vertexBuffer)
        {
            vertexBuffer.m_glId;
        }
    };
}
