#pragma once

#include "stdafx.hpp"

#include "Texture.hpp"

//#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"

namespace gfx_test
{
    namespace imp
    {
        template<Dimensions D, AntiAliasing A>
        class GTexture<GraphicsAPI::OpenGL, D, A> : public DTexture<D>
        {
        public:
            GTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const DTexture<D>::Vector& dimensions)
                : DTexture<D>{ format, filter, wrapping, dimensions }
            {

            }

        private:
            GLuint m_glId{};
            GLuint m_glFormat{};
            GLuint m_glMinFilter{};
            GLuint m_glMagFilter{};
            GLuint m_glWrapping{};
        };
    }
}