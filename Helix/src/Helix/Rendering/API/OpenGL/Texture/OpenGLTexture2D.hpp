#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Texture2D.hpp"

namespace hlx
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(Format format, ColorDepth colorDepth, const Vector2u& dimensions, Filter filter, Wrapping wrappingS, Wrapping wrappingT, unsigned int mipLevels, bool sRGB);
        OpenGLTexture2D(Format format, ColorDepth colorDepth, const Vector2u& dimensions, Filter filter, Wrapping wrappingS, Wrapping wrappingT, unsigned int mipLevels, bool sRGB, Format dataFormat, std::span<const byte> data);
		~OpenGLTexture2D() override;
		
		void bind() const override;
		void bind(unsigned int slot) const override;
		void unbind() const override;
		bool is_bound() const override;
		
        void copy(Format dataFormat, std::span<const byte> data, unsigned int mipLevel = 0, bool generateMips = true) override;
		void copy_range(const Vector2u& dimensions, const Vector2u& offset, Format dataFormat, std::span<const byte> data, unsigned int mipLevel = 0, bool generateMips = true) override;

	private:
		GLenum m_internalTarget{ GL_TEXTURE_2D };
		GLenum m_internalFormat{};
		GLenum m_internalLayout{};
	};
}
