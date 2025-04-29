#pragma once

#include "stdafx.hpp"

#include "Flags.hpp"

namespace fox::gfx::api::gl
{
    template<glf::Texture::Target T, glf::Texture::Target U>
    concept valid_texture_view = 
        (T == glf::Texture::Target::_1D                 && (U == glf::Texture::Target::_1D            || U == glf::Texture::Target::_1DArray)                                                                                              ) ||
        (T == glf::Texture::Target::_2D                 && (U == glf::Texture::Target::_2D            || U == glf::Texture::Target::_2DArray)                                                                                              ) ||
        (T == glf::Texture::Target::_3D                 && (U == glf::Texture::Target::_3D)                                                                                                                                                ) ||
        (T == glf::Texture::Target::CubeMap             && (U == glf::Texture::Target::CubeMap        || U == glf::Texture::Target::_2D                 || U == glf::Texture::Target::_2DArray || U == glf::Texture::Target::CubeMapArray) ) ||
        (T == glf::Texture::Target::Rectangle           && (U == glf::Texture::Target::Rectangle)                                                                                                                                          ) ||
        (T == glf::Texture::Target::_1DArray            && (U == glf::Texture::Target::_1D            || U == glf::Texture::Target::_1DArray)                                                                                              ) ||
        (T == glf::Texture::Target::_2DArray            && (U == glf::Texture::Target::_2D            || U == glf::Texture::Target::_2DArray)                                                                                              ) ||
        (T == glf::Texture::Target::CubeMapArray        && (U == glf::Texture::Target::_2D            || U == glf::Texture::Target::_2DArray            || U == glf::Texture::Target::CubeMap  || U == glf::Texture::Target::CubeMapArray) ) ||
        (T == glf::Texture::Target::_2DMultisample      && (U == glf::Texture::Target::_2DMultisample || U == glf::Texture::Target::_2DMultisampleArray)                                                                                   ) ||
        (T == glf::Texture::Target::_2DMultisampleArray && (U == glf::Texture::Target::_2DMultisample || U == glf::Texture::Target::_2DMultisampleArray));
}
