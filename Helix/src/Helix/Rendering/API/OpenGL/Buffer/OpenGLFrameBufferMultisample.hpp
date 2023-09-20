#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2DMultisample.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLRenderBufferMultisample.hpp"
#include "Helix/Rendering/Buffer/FrameBufferMultisample.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"
#include "Helix/Rendering/Blueprint/RenderBufferBlueprint.hpp"

namespace hlx
{
    class OpenGLFrameBufferMultisample : public FrameBufferMultisample
    {
    public:
        OpenGLFrameBufferMultisample(const Vector2u& dimensions, unsigned int samples, std::span<const TextureManifest> textureManifest, std::span<const RenderBufferManifest> renderBufferManifest);
        ~OpenGLFrameBufferMultisample();

        void bind(Target target) const override;
        void unbind()            const override;
        bool is_bound()          const override;

        void bind_texture(const std::string& identifier, unsigned int slot) const override;

        GLuint internal_id() const
        {
            return m_internalId;
        }

    private:
        GLuint m_internalId{};
    };
}
