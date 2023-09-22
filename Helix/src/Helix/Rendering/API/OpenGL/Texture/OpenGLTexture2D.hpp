#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Texture2D.hpp"

namespace hlx
{
	class OpenGLTexture2D: public Texture2D
	{
	public:
		OpenGLTexture2D(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions);
		OpenGLTexture2D(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions, Components components, std::span<const byte> data);
		~OpenGLTexture2D() override;
		
		void bind(unsigned int slot) const override;
		
		GLuint id() const
		{
			return m_id;
		}

	protected:
        void copy(Components components, std::span<const byte> data) override;
        void copy_range(const Vector2u& dimensions, const Vector2u& offset, Components components, std::span<const byte> data) override;

	private:
		GLuint m_id{};
	};
}
