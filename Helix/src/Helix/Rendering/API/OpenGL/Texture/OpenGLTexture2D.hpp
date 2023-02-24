#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Texture2D.hpp"

namespace hlx
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(Format format, Layout layout, const Vector2u& dimensions, unsigned int mipLevels, Wrapping wrappingS, Wrapping wrappingT, Filter filter, std::span<const byte> data = {});
		~OpenGLTexture2D() override;
		
		void bind() const override;
		void bind(unsigned int slot) const override;
		void unbind() const override;
		bool bound() const override;
		
        void copy(std::span<const byte> data, unsigned int mipLevel = 0, bool generateMips = true) override;
		void copy_range(const Vector2u& dimensions, const Vector2u& offset, std::span<const byte> data, unsigned int mipLevel = 0, bool generateMips = true) override;

	private:
		GLenum m_internalTarget{ GL_TEXTURE_2D };
		GLenum m_internalFormat{};
		GLenum m_internalLayout{};
	};
}
