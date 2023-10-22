#pragma once

#include "Helix/Experimental/Rendering/Buffer/VertexArray.hpp"
#include "OpenGLBuffer.hpp"

namespace hlx::gfx::api
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

        }
    };
}
