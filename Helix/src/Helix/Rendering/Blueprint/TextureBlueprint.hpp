#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Texture/Texture2D.hpp"
#include "Helix/IO/Filesystem/Image.hpp"

namespace hlx
{
	struct TextureBlueprint
	{
	public:
		TextureBlueprint() = default;

		std::shared_ptr<Texture2D> build(const std::shared_ptr<Image> image, unsigned int mipLevels) const;
		std::shared_ptr<Texture2D> build(const glm::uvec2& dimensions, unsigned int mipLevels) const;

		Texture::Format    format{ Texture::Format::RGBA };
		Texture::Layout    layout{ Texture2D::Layout::RGBA8 };
		Texture::Wrapping  wrappingS{ Texture2D::Wrapping::ClampToEdge };
		Texture::Wrapping  wrappingT{ Texture2D::Wrapping::ClampToEdge };
		Texture::MinFilter minFilter{ Texture2D::MinFilter::NearestMipmapNearest };
		Texture::MagFilter magFilter{ Texture2D::MagFilter::Nearest };
	};
}
