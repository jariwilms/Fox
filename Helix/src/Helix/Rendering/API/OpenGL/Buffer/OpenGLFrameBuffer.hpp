#pragma once

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
		OpenGLFrameBuffer(const Vector2u& dimensions, const std::vector<std::tuple<std::string, Attachment, TextureBlueprint>>& textures, const std::vector<std::tuple<std::string, Attachment, RenderBufferBlueprint>>& renderBuffers);
		~OpenGLFrameBuffer();

		void bind(Target target) override;
		void unbind() const override;
		bool bound() const override;

		void bind_texture(const std::string identifier, unsigned int slot) override;

	private:
		GLenum m_internalBoundTarget{};
	};
}
