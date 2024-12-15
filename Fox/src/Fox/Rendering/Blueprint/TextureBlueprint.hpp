#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/Texture/Texture.hpp"

namespace fox::gfx::api
{
    struct TextureBlueprint
    {
    public:
        TextureBlueprint(Texture::Format format, Texture::Filter filter = Texture::Filter::Trilinear, Texture::Wrapping wrapping = Texture::Wrapping::Repeat)
            : format{ format }, filter{ filter }, wrapping{ wrapping } {}

        Texture::Format   format{};
        Texture::Filter   filter{};
        Texture::Wrapping wrapping{};
    };
}
