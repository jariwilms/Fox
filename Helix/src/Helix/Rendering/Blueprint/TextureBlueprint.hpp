#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Texture/Texture2D.hpp"
#include "Helix/Rendering/Texture/Texture2DMultisample.hpp"
#include "Helix/IO/Filesystem/Image.hpp"

namespace hlx
{
	struct TextureBlueprint
	{
	public:
		TextureBlueprint() = default;

		std::shared_ptr<Texture2D> build(const std::shared_ptr<Image> image, unsigned int mipLevels = 1) const;
		std::shared_ptr<Texture2D> build(const Vector2u& dimensions, unsigned int mipLevels = 1) const;
		std::shared_ptr<Texture2DMultisample> build_ms(const Vector2u& dimensions, unsigned int mipLevels = 1, unsigned int samples = 0) const;

		Texture::Format   format{ Texture::Format::RGBA };
		Texture::Layout   layout{ Texture::Layout::RGBA8 };
		Texture::Wrapping wrappingS{ Texture::Wrapping::ClampToEdge };
		Texture::Wrapping wrappingT{ Texture::Wrapping::ClampToEdge };
		Texture::Filter   filter{ Texture::Filter::Point };
	};
}
