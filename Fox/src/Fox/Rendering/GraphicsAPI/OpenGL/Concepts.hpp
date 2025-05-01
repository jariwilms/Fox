#pragma once

#include "stdafx.hpp"

#include "Flags.hpp"

namespace fox::gfx::api::gl
{
    template<typename T>
    concept arithmetic_type_c =
        (
            std::is_same_v<T, gl::int8_t>    || 
            std::is_same_v<T, gl::uint8_t>   || 
            std::is_same_v<T, gl::int16_t>   || 
            std::is_same_v<T, gl::uint16_t>  || 
            std::is_same_v<T, gl::int32_t>   || 
            std::is_same_v<T, gl::uint32_t>  || 
            std::is_same_v<T, gl::int64_t>   || 
            std::is_same_v<T, gl::uint64_t>  || 
            std::is_same_v<T, gl::float16_t> ||
            std::is_same_v<T, gl::float32_t> || 
            std::is_same_v<T, gl::float64_t>
        );

    template<glf::Texture::Target T, glf::Texture::Target U>
    concept valid_texture_view_c = 
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
