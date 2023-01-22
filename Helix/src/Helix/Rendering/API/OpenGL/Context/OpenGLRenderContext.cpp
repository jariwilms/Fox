#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "OpenGLRenderContext.hpp"
#include "Helix/Window/API/GLFW/GLFWWindow.hpp"

namespace hlx
{
	OpenGLRenderContext::OpenGLRenderContext()
	{

	}
	OpenGLRenderContext::~OpenGLRenderContext()
	{

	}

    void OpenGLRenderContext::gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param)
    {
        const auto sourceMessage = [source]() -> std::string
        {
            switch (source)
            {
                case GL_DEBUG_SOURCE_API:             return "API";
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   return "WINDOW_SYSTEM";
                case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER_COMPILER";
                case GL_DEBUG_SOURCE_THIRD_PARTY:     return "THIRD_PARTY";
                case GL_DEBUG_SOURCE_APPLICATION:     return "APPLICATION";
                case GL_DEBUG_SOURCE_OTHER:           return "OTHER";

                default:                              throw std::invalid_argument{ "Invalid source!" };
            }
        }();
        const auto typeMessage = [type]() -> std::string
        {
            switch (type)
            {
                case GL_DEBUG_TYPE_ERROR:               return "ERROR";
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "UNDEFINED_BEHAVIOR";
                case GL_DEBUG_TYPE_PORTABILITY:         return "PORTABILITY";
                case GL_DEBUG_TYPE_PERFORMANCE:         return "PERFORMANCE";
                case GL_DEBUG_TYPE_MARKER:              return "MARKER";
                case GL_DEBUG_TYPE_OTHER:               return "OTHER";

                default:                                throw std::invalid_argument{ "Invalid type!" };
            }
        }();
        const auto severityMessage = [severity]() -> std::string
        {
            switch (severity)
            {
                case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
                case GL_DEBUG_SEVERITY_LOW:          return "LOW";
                case GL_DEBUG_SEVERITY_MEDIUM:       return "MEDIUM";
                case GL_DEBUG_SEVERITY_HIGH:         return "HIGH";

                default:                             throw std::invalid_argument{ "Invalid severity!" };
            }
        }();

        std::cout << std::format("[GL_DEBUG] {0}, {1}, {2}, {3}: {4}\n", sourceMessage, typeMessage, severityMessage, id, message);
    }
}
