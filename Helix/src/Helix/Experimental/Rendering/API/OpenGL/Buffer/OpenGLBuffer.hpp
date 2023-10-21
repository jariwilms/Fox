#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Experimental/Rendering/Buffer/Buffer.hpp"
#include "Helix/Experimental/Rendering/Buffer/VertexArray.hpp"

namespace hlx::gfx::imp
{
    template<Buffer::Type S, typename T>
    class GBuffer<GraphicsAPI::OpenGL, S, T> : public Buffer
    {
    public:
        GBuffer(std::vector<T> data)
        {

        }
        GBuffer(u32 count)
        {

        }

    private:
        friend GVertexArray<GraphicsAPI::OpenGL>;

        GLuint m_glId{};
    };
}
