#pragma once

#include "stdafx.hpp"

#include "Rendering/Rendering.hpp"
#include "Helix/Core/Library/Utility/Utility.hpp"

void experimental()
{
    using namespace hlx::gfx;

    //std::vector<byte> data{};
    //Texture1D t1d{ Texture::Format::D16_UNORM, Texture::Filter::Bilinear, Texture::Wrapping::ClampToBorder, Vector1u{ 2u }, hlx::utl::to_span(data) };
    //Texture2D t2d{ Texture::Format::D16_UNORM, Texture::Filter::Bilinear, Texture::Wrapping::ClampToBorder, Vector2u{ 2u, 3u }, hlx::utl::to_span(data) };
    //Texture3D t3d{ Texture::Format::D16_UNORM, Texture::Filter::Bilinear, Texture::Wrapping::ClampToBorder, Vector3u{ 2u, 3u, 4u } };



    using L1 = Layout<float, 3>;
    using L2 = Layout<int, 2>;
    VertexLayout<L1, L2> l{};

    auto vb1 = std::make_shared<VertexBuffer<float>>(12);
    auto ib1 = std::make_shared<IndexBuffer>(2);
    VertexArray va{};
    



    FrameBuffer fb{ Vector2u{}, std::span<const FrameBuffer::Manifest>{} };

    va.tie(vb1, l);
    va.tie(ib1);
}
