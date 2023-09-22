#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2D.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLRenderBuffer.hpp"
#include "Helix/Rendering/Buffer/FrameBuffer.hpp"

namespace hlx
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const Vector2u& dimensions, std::span<const TextureManifest> textureManifests, std::span<const RenderBufferManifest> renderBufferManifests);
		~OpenGLFrameBuffer();

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

        std::unordered_map<std::string, std::shared_ptr<OpenGLTexture2D>>    m_textures{};
        std::unordered_map<std::string, std::shared_ptr<OpenGLRenderBuffer>> m_renderBuffers{};
	};
}
