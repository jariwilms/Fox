#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Texture/Texture2D.hpp"
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
			const auto buffer = image->read(true);
			std::span<byte> data{ buffer->begin(), buffer->size() };

			return GraphicsAPI::create_tex(format, layout, wrappingS, wrappingT, minFilter, magFilter, image->dimensions(), data);
		}

		template<typename T, typename... Args>
		std::shared_ptr<T> reserve(Args...) const = delete;
		template<> std::shared_ptr<Texture2D> reserve(const glm::uvec2& dimensions) const
		{
			return std::make_shared<OpenGLTexture2D>(format, layout, wrappingS, wrappingT, minFilter, magFilter, dimensions);
		}

		Texture::Format   format{ Texture::Format::RGBA };
		Texture::Layout   layout{ Texture2D::Layout::RGBA8 };
		Texture::Wrapping wrappingS{ Texture2D::Wrapping::ClampToEdge };
		Texture::Wrapping wrappingT{ Texture2D::Wrapping::ClampToEdge };
		Texture::Filter   minFilter{ Texture2D::Filter::Nearest };
		Texture::Filter   magFilter{ Texture2D::Filter::Nearest };
	};
}
