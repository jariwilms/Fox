#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Def.hpp"
#include "Renderer.hpp"

void experimental()
{
    using namespace def;

    Texture1D t1d{ Texture::Format::D16_UNORM, Texture::Filter::Bilinear, Texture::Wrapping::ClampToBorder, Vector1u{ 2u } };
    Texture2D t2d{ Texture::Format::D16_UNORM, Texture::Filter::Bilinear, Texture::Wrapping::ClampToBorder, Vector2u{ 2u, 3u } };
    Texture3D t3d{ Texture::Format::D16_UNORM, Texture::Filter::Bilinear, Texture::Wrapping::ClampToBorder, Vector3u{ 2u } };
}
