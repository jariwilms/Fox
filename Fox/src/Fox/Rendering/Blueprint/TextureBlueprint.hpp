#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/Texture/Texture.hpp"

namespace fox::gfx::api
{
    struct TextureBlueprint
    {
    public:
        TextureBlueprint(Texture::Format format)
            : TextureBlueprint{ format, Texture::Filter{}, Texture::Wrapping{} } {}
        TextureBlueprint(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping)
            : format{ format }, filter{ filter }, wrapping{ wrapping } {}

        Texture::Format   format{};
        Texture::Filter   filter{};
        Texture::Wrapping wrapping{};
    };
}
