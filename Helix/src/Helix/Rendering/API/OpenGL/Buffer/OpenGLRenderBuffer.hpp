#pragma once

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Buffer/RenderBuffer.hpp"

namespace hlx
{
	class OpenGLRenderBuffer : public RenderBuffer
	{
	public:
		OpenGLRenderBuffer(RenderBuffer::Format format, const Vector2u& dimensions);
		~OpenGLRenderBuffer();

		void bind() const override;

		GLuint id() const
		{
			return m_id;
		}

	private:
		GLuint m_id{};
	};
}
