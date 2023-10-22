#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"
#include "Helix/Experimental/Rendering/Buffer/FrameBuffer.hpp"

namespace hlx::gfx::api
{
    template<AntiAliasing A>
    class GFrameBuffer<GraphicsAPI::OpenGL, A> : public FrameBuffer<A>
    {
    public:
        GFrameBuffer(const Vector2u& dimensions)
        {

        }

        void bind(FrameBuffer::Target target)
        {

        }
        void bind_texture(std::string_view identifier, unsigned int slot)
        {

        }

    private:
        GLuint m_glId{};
    };
}
