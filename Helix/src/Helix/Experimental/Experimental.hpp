#pragma once

#include "stdafx.hpp"

#include "Rendering/Def.hpp"
#include "Helix/Core/Library/Utility/Utility.hpp"

void experimental()
{
    using namespace hlx::gfx;

    std::vector<byte> data{};

    Texture1D t1d{ Texture::Format::D16_UNORM, Texture::Filter::Bilinear, Texture::Wrapping::ClampToBorder, Vector1u{ 2u }, hlx::utl::to_span(data) };
    Texture2D t2d{ Texture::Format::D16_UNORM, Texture::Filter::Bilinear, Texture::Wrapping::ClampToBorder, Vector2u{ 2u, 3u }, hlx::utl::to_span(data) };
    Texture3D t3d{ Texture::Format::D16_UNORM, Texture::Filter::Bilinear, Texture::Wrapping::ClampToBorder, Vector3u{ 2u, 3u, 4u } };

    t1d.bind(0);



    VertexArray va{};
    VertexBuffer<float> vb1{ 12 };

    va.tie(vb1);
}
