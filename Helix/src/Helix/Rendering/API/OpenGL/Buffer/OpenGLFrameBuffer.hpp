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
		OpenGLFrameBuffer(const Vector2u& dimensions, const std::vector<Texture2DBlueprintSpec>& textures, const std::vector<RenderBufferBlueprintSpec>& renderBuffers, Option options = Option::None);
		~OpenGLFrameBuffer();

		void bind(Target target) override;
		void unbind() const override;
		bool is_bound() const override;

		void bind_texture(const std::string& identifier, unsigned int slot) override;

		std::shared_ptr<Texture2D> texture(const std::string& identifier) override;

	private:
		GLenum m_internalBoundTarget{};
	};
}
