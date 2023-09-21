#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2D.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLRenderBuffer.hpp"
#include "Helix/Rendering/Buffer/FrameBuffer.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"
#include "Helix/Rendering/Blueprint/RenderBufferBlueprint.hpp"

namespace hlx
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const Vector2u& dimensions, std::span<const TextureManifest> textureManifest, std::span<const RenderBufferManifest> renderBufferManifest);
		~OpenGLFrameBuffer();

		void bind(Target target) const override;

		void bind_texture(const std::string& identifier, unsigned int slot) const override;

		GLuint id() const
		{
			return m_id;
		}

	private:
		GLuint m_id{};
	};
}
