#pragma once

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2D.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLRenderBuffer.hpp"
#include "Helix/Rendering/Buffer/FrameBuffer.hpp"

namespace hlx
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const glm::uvec2& dimensions);
		~OpenGLFrameBuffer();

		void bind() const override;
		void bind(FrameBuffer::Target target) const override;
		void unbind() const override;
		bool is_bound() const override;

	private:

	};
}
