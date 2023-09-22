#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2DMultisample.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLRenderBufferMultisample.hpp"
#include "Helix/Rendering/Buffer/FrameBufferMultisample.hpp"

namespace hlx
{
    class OpenGLFrameBufferMultisample : public FrameBufferMultisample
    {
    public:
        OpenGLFrameBufferMultisample(const Vector2u& dimensions, unsigned int samples, std::span<const TextureManifest> textureManifests, std::span<const RenderBufferManifest> renderBufferManifests);
        ~OpenGLFrameBufferMultisample();

        void bind(Target target) const override;
        void bind_texture(const std::string& identifier, unsigned int slot) const override;

        GLuint id() const
        {
            return m_id;
        }

    private:
        GLenum attach_texture(const TextureManifest& textureManifest, unsigned int& attachmentIndex);
        void   attach_renderbuffer(const RenderBufferManifest& renderBufferManifest);

        GLuint m_id{};

        std::unordered_map<std::string, std::shared_ptr<OpenGLTexture2DMultisample>>    m_textures{};
        std::unordered_map<std::string, std::shared_ptr<OpenGLRenderBufferMultisample>> m_renderBuffers{};
    };
}
