#pragma once

#include "Flags.hpp"

namespace fox::gfx::api::gl
{
    template<glf::Feature F>
    concept indexable_feature = (F == glf::Feature::Blending or F == glf::Feature::ScissorTest);

    template<typename T>
    concept arithmetic_type_c =
        (
               std::is_same_v<T, gl::int8_t>     
            or std::is_same_v<T, gl::uint8_t>
            or std::is_same_v<T, gl::int16_t>
            or std::is_same_v<T, gl::uint16_t>
            or std::is_same_v<T, gl::int32_t>
            or std::is_same_v<T, gl::uint32_t>
            or std::is_same_v<T, gl::int64_t>
            or std::is_same_v<T, gl::uint64_t>
            or std::is_same_v<T, gl::float16_t>
            or std::is_same_v<T, gl::float32_t>
            or std::is_same_v<T, gl::float64_t>
        );

    template<glf::Texture::Target T, glf::Texture::Target U>
    concept valid_texture_view_c = 
           (T == glf::Texture::Target::_1D                 and (U == glf::Texture::Target::_1D            or U == glf::Texture::Target::_1DArray           )                                                                                   )
        or (T == glf::Texture::Target::_2D                 and (U == glf::Texture::Target::_2D            or U == glf::Texture::Target::_2DArray           )                                                                                   )
        or (T == glf::Texture::Target::_3D                 and (U == glf::Texture::Target::_3D                                                             )                                                                                   )
        or (T == glf::Texture::Target::CubeMap             and (U == glf::Texture::Target::CubeMap        or U == glf::Texture::Target::_2D                  or U == glf::Texture::Target::_2DArray or U == glf::Texture::Target::CubeMapArray))
        or (T == glf::Texture::Target::Rectangle           and (U == glf::Texture::Target::Rectangle                                                       )                                                                                   )
        or (T == glf::Texture::Target::_1DArray            and (U == glf::Texture::Target::_1D            or U == glf::Texture::Target::_1DArray           )                                                                                   )
        or (T == glf::Texture::Target::_2DArray            and (U == glf::Texture::Target::_2D            or U == glf::Texture::Target::_2DArray           )                                                                                   )
        or (T == glf::Texture::Target::CubeMapArray        and (U == glf::Texture::Target::_2D            or U == glf::Texture::Target::_2DArray             or U == glf::Texture::Target::CubeMap  or U == glf::Texture::Target::CubeMapArray))
        or (T == glf::Texture::Target::_2DMultisample      and (U == glf::Texture::Target::_2DMultisample or U == glf::Texture::Target::_2DMultisampleArray)                                                                                   )
        or (T == glf::Texture::Target::_2DMultisampleArray and (U == glf::Texture::Target::_2DMultisample or U == glf::Texture::Target::_2DMultisampleArray)                                                                                   );
}
