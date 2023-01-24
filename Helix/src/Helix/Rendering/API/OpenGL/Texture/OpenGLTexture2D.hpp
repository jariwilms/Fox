#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Texture2D.hpp"

namespace hlx
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const glm::uvec2& dimensions);
		OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const glm::uvec2& dimensions, const std::span<byte>& data);
		OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const glm::uvec2& dimensions, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter, unsigned int levels);
		OpenGLTexture2D(Texture::Format format, Texture::Layout layout, const glm::uvec2& dimensions, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter, unsigned int levels, const std::span<byte>& data);
		~OpenGLTexture2D() override;
		
		void bind() const override;
		void bind(unsigned int slot) const override;
		void unbind() const override;
		bool is_bound() const override;
		
		void copy(const glm::uvec2& dimensions, const glm::uvec2& offset, const std::span<byte>& data) const override;

	private:
		GLenum m_internalTarget{ GL_TEXTURE_2D };
		GLenum m_internalFormat{};
		GLenum m_internalLayout{};
	};
}
