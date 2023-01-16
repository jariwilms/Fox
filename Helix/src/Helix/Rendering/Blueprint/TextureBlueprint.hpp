#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Texture/Texture2D.hpp"
#include "Helix/Rendering/Texture/Texture3D.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2D.hpp"
#include "Helix/IO/Filesystem/Image.hpp"

namespace hlx
{
	struct TextureBlueprint
	{
	public:
		TextureBlueprint() = default;

		template<typename T>
		std::shared_ptr<T> build(const std::shared_ptr<Image> image) const = delete;
		template<> std::shared_ptr<Texture2D> build(const std::shared_ptr<Image> image) const 
		{
			const auto buffer     = image->read();
			const auto data       = std::span<byte>{ buffer->begin(), buffer->size() };
			const auto dimensions = glm::uvec3{ image->dimensions(), 0u };

			return std::make_shared<OpenGLTexture2D>(format, layout, wrappingS, wrappingT, minFilter, magFilter, dimensions, data);
		}

		template<typename T, typename... Args>
		std::shared_ptr<T> reserve(Args...) const = delete;
		template<> std::shared_ptr<Texture2D> reserve(const glm::uvec2& dimensions) const
		{
			return std::make_shared<OpenGLTexture2D>(format, layout, wrappingS, wrappingT, minFilter, magFilter, dimensions);
		}
		template<> std::shared_ptr<Texture3D> reserve(const glm::uvec3& dimensions) const
		{
			return {};
			//return std::make_shared<OpenGLTexture2D>(format, layout, wrappingS, wrappingT, minFilter, magFilter, dimensions);
		}

		Texture::Format   format{ Texture::Format::RGBA };
		Texture::Layout   layout{ Texture2D::Layout::RGBA8 };
		Texture::Wrapping wrappingS{ Texture2D::Wrapping::ClampToEdge };
		Texture::Wrapping wrappingT{ Texture2D::Wrapping::ClampToEdge };
		Texture::Wrapping wrappingR{ Texture2D::Wrapping::ClampToEdge };
		Texture::Filter   minFilter{ Texture2D::Filter::Nearest };
		Texture::Filter   magFilter{ Texture2D::Filter::Nearest };
	};
}
