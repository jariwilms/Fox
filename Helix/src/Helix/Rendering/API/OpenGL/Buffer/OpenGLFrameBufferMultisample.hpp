#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Buffer/FrameBufferMultisample.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"
#include "Helix/Rendering/Blueprint/RenderBufferBlueprint.hpp"

namespace hlx
{
    class OpenGLFrameBufferMultisample : public FrameBufferMultisample
    {
    public:
        OpenGLFrameBufferMultisample(const Vector2u& dimensions, unsigned int samples, const std::vector<std::tuple<std::string, Attachment, TextureBlueprint>>& textures, const std::vector<std::tuple<std::string, Attachment, RenderBufferBlueprint>>& renderBuffers);
        ~OpenGLFrameBufferMultisample();

        void bind(Target target) override;
        void unbind() const override;
        bool bound() const override;

        void bind_texture(const std::string identifier, unsigned int slot) override;

    private:
        GLenum m_internalBoundTarget{};
    };
}
