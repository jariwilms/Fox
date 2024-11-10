#ifndef FOX_GRAPHICS_API
#define FOX_GRAPHICS_API OpenGL
#endif

#if FOX_GRAPHICS_API == OpenGL
#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#elif FOX_GRAPHICS_API == Vulkan
#include "Fox/Rendering/API/Vulkan/Vulkan.hpp"
#elif FOX_GRAPHICS_API == DirectX12
#include "Fox/Rendering/API/DirectX/DirectX.hpp"
#endif
