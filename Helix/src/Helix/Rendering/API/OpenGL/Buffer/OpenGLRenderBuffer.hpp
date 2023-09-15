#pragma once

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Buffer/RenderBuffer.hpp"

namespace hlx
{
	class OpenGLRenderBuffer : public RenderBuffer
	{
	public:
		OpenGLRenderBuffer(RenderBuffer::Type type, RenderBuffer::Layout layout, const Vector2u& dimensions);
		~OpenGLRenderBuffer();

		void bind() const override;
		void unbind() const override;
		bool is_bound() const override;

		GLuint internal_id()     const
		{
			return m_internalId;
		}
		GLenum internal_target() const
		{
			return m_internalTarget;
		}
		GLenum internal_format() const
		{
			return m_internalFormat;
		}

	private:
		GLuint m_internalId{};
		GLenum m_internalTarget{};
		GLenum m_internalFormat{};

		static inline GLuint s_boundRenderBufferId{};
	};
}
