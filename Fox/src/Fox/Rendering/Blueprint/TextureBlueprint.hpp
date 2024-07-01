#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/Texture/Texture.hpp"

namespace fox::gfx::api
{
    struct TextureBlueprint
    {
        Texture::Format   format{};
        Texture::Filter   filter{};
        Texture::Wrapping wrapping{};
    };
}
