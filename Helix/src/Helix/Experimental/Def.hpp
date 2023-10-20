#pragma once

#include "stdafx.hpp"

#include "Texture.hpp"
#include "OpenGLTexture.hpp"



namespace def
{
    constexpr auto GRAPHICS_API = gfx_test::imp::GraphicsAPI::OpenGL;

    using Texture = gfx_test::imp::Texture;

    using Texture1D    = gfx_test::imp::GTexture<GRAPHICS_API, gfx_test::imp::Dimensions::_1D, gfx_test::imp::AntiAliasing::None>;
    using Texture2D    = gfx_test::imp::GTexture<GRAPHICS_API, gfx_test::imp::Dimensions::_2D, gfx_test::imp::AntiAliasing::None>;
    using Texture2D_AA = gfx_test::imp::GTexture<GRAPHICS_API, gfx_test::imp::Dimensions::_2D, gfx_test::imp::AntiAliasing::MSAA>;
    using Texture3D    = gfx_test::imp::GTexture<GRAPHICS_API, gfx_test::imp::Dimensions::_3D, gfx_test::imp::AntiAliasing::None>;
}