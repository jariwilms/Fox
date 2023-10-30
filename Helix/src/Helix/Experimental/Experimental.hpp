#pragma once

#include "stdafx.hpp"

#include "Rendering/Rendering.hpp"
#include "Helix/Core/Library/Utility/Utility.hpp"

void experimental()
{
    using namespace hlx;

    gfx::Texture2D asd{ gfx::Texture::Format::D16_UNORM, gfx::Texture::Filter::Bilinear, gfx::Texture::Wrapping::ClampToBorder, Vector2u{} };
}
