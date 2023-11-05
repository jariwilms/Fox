#if HLX_GRAPHICS_API == OpenGL
#include "Helix/Rendering/API/OpenGL/Renderer/OpenGLRenderer.hpp"
#endif

#if HLX_GRAPHICS_API == Vulkan
//#include "Helix/Rendering/API/Vulkan/VulkanRenderer.hpp"
#endif

namespace hlx::gfx
{
    using Renderer = imp::api::GRenderer<api::GRAPHICS_API>;
}
