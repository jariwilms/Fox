#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/API/RenderContextAPI.hpp"

namespace hlx
{
	class OpenGLRenderContext : public RenderContextAPI
	{
	public:
		OpenGLRenderContext();
		~OpenGLRenderContext() override;

		void gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param);
	};
}
