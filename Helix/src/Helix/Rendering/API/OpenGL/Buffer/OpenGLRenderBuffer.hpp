#pragma once

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Buffer/RenderBuffer.hpp"

namespace hlx
{
	class OpenGLRenderBuffer : public RenderBuffer
	{
	public:
		OpenGLRenderBuffer(RenderBuffer::Type type, RenderBuffer::Layout layout, const glm::uvec2& dimensions, unsigned int samples);
		~OpenGLRenderBuffer();

		void bind() const override;
		void unbind() const override;
		bool is_bound() const override;

	private:
		GLenum m_internalTarget{ GL_RENDERBUFFER };
		GLenum m_internalFormat{};
	};
}
