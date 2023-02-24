#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "OpenGLRenderContext.hpp"
#include "Helix/Window/API/GLFW/GLFWWindow.hpp"
#include "Helix/Window/WindowManager.hpp"

namespace hlx
{
	OpenGLRenderContext::OpenGLRenderContext()
	{
        static auto self = this;
        const auto forward_gl_debug_callback = [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* param)
        {
            //const auto glfwWindow = reinterpret_cast<GLFWwindow*>(WindowManager::find("Window 1")->native_window()); //TODO: fix how UserPointer is fetched
            //const auto userPointer = static_cast<GLFWWindow::UserPointer*>(glfwGetWindowUserPointer(glfwWindow));

            //const auto& context = userPointer->renderContext;
            self->gl_debug_callback(source, type, id, severity, length, message, param);
        };

#ifdef HLX_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(forward_gl_debug_callback, nullptr);
#endif
        glEnable(GL_MULTISAMPLE); //TODO: move to renderer ctor?
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
