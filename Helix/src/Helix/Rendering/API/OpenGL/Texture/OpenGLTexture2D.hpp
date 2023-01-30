#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Texture2D.hpp"

namespace hlx
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels);
		OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, std::span<const byte> data);
		OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter);
		OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter, std::span<const byte> data);
		~OpenGLTexture2D() override;
		
		void bind() const override;
		void bind(unsigned int slot) const override;
		void unbind() const override;
		bool bound() const override;
		
		void copy(const Vector2u& dimensions, const Vector2u& offset, std::span<const byte> data) const override;

	private:
		GLenum m_internalTarget{ GL_TEXTURE_2D };
		GLenum m_internalFormat{};
		GLenum m_internalLayout{};
	};
}
