#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/Texture/Texture.hpp"

namespace hlx::gfx::api
{
    struct TextureBlueprint
    {
        Texture::Format   format{};
        Texture::Filter   filter{};
        Texture::Wrapping wrapping{};
    };
}
