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

			return GraphicsAPI::create_tex(format, layout, image->dimensions(), wrappingS, wrappingT, minFilter, magFilter, levels, data);
		}

		template<typename T, typename... Args>
		std::shared_ptr<T> reserve(Args...) const = delete;
		template<> std::shared_ptr<Texture2D> reserve(const glm::uvec2& dimensions) const
		{
			return std::make_shared<OpenGLTexture2D>(format, layout, dimensions, wrappingS, wrappingT, minFilter, magFilter, levels);
		}

		Texture::Format    format{ Texture::Format::RGBA };
		Texture::Layout    layout{ Texture2D::Layout::RGBA8 };
		Texture::Wrapping  wrappingS{ Texture2D::Wrapping::ClampToEdge };
		Texture::Wrapping  wrappingT{ Texture2D::Wrapping::ClampToEdge };
		Texture::MinFilter minFilter{ Texture2D::MinFilter::LinearMipmapLinear };
		Texture::MagFilter magFilter{ Texture2D::MagFilter::Linear };
		unsigned int       levels{ 1 };
	};
}
