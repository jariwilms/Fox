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
		OpenGLFrameBuffer(const glm::uvec2& dimensions, const std::vector<std::tuple<std::string, Attachment, TextureBlueprint>>& textures, const std::vector<std::tuple<std::string, Attachment, RenderBufferBlueprint>>& renderBuffers);
		~OpenGLFrameBuffer();

		void bind() const override;
		void bind(FrameBuffer::Target target) const override;
		void unbind() const override;
		bool is_bound() const override;

		void bind_texture(const std::string identifier, unsigned int slot) override;
	};
}
