#if FOX_GRAPHICS_API == OpenGL
#include "Fox/Rendering/API/OpenGL/Renderer/OpenGLRenderer.hpp"
#endif

#if FOX_GRAPHICS_API == Vulkan
//#include "Fox/Rendering/API/Vulkan/VulkanRenderer.hpp"
#endif

namespace fox::gfx
{
    //using Renderer = imp::api::GRenderer<api::GRAPHICS_API>;
    using Renderer = api::gl::OpenGLRenderer;
}
