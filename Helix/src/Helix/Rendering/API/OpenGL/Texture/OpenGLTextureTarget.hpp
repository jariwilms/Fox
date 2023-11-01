#pragma once

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Dimensions.hpp"

namespace hlx::gfx::api
{
    template<Dimensions>
    struct DimensionsToTarget;
    template<> struct DimensionsToTarget<Dimensions::_1D> { static inline GLenum target = GL_TEXTURE_1D; };
    template<> struct DimensionsToTarget<Dimensions::_2D> { static inline GLenum target = GL_TEXTURE_2D; };
    template<> struct DimensionsToTarget<Dimensions::_3D> { static inline GLenum target = GL_TEXTURE_3D; };
}
