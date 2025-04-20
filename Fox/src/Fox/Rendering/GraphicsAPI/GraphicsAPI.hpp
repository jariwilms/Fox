#pragma once

#define FOX_GRAPHICS_API_DIRECTX 1
#define FOX_GRAPHICS_API_OPENGL  2
#define FOX_GRAPHICS_API_VULKAN  3

#ifndef FOX_GRAPHICS_API
#define FOX_GRAPHICS_API FOX_GRAPHICS_API_OPENGL
#endif

#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"
#endif

namespace fox::gfx
{
    namespace api
    {
        namespace dx {}
        namespace gl {}
        namespace vk {}
    }

#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
    using handle_t = api::gl::handle_t;
#endif
}
