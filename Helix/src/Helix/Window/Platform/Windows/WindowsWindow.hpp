#pragma once

#include "stdafx.hpp"

#include "Helix/Window/Window.hpp"

namespace hlx
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const Window::Properties& properties);
		~WindowsWindow() override;

		void rename(std::string_view title) override;
		void resize(const glm::vec2& dimensions) override;
		void switch_mode(const DisplayMode& displayMode) override;

		void refresh() override;

		NativeWindow native_window() const override;

	private:
		static void _windowDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
		{
			auto const src_str = [source]() //TODO: rename variables (src_str => srcStr)
			{
				switch (source)
				{
					case GL_DEBUG_SOURCE_API:             return "API";
					case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   return "WINDOW SYSTEM";
					case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
					case GL_DEBUG_SOURCE_THIRD_PARTY:     return "THIRD PARTY";
					case GL_DEBUG_SOURCE_APPLICATION:     return "APPLICATION";
					case GL_DEBUG_SOURCE_OTHER:           return "OTHER";

					default:                              throw std::invalid_argument{ "Invalid source!" };
				}
			}();

			auto const type_str = [type]()
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

			auto const severity_str = [severity]()
			{
				switch (severity) {
					case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
					case GL_DEBUG_SEVERITY_LOW:          return "LOW";
					case GL_DEBUG_SEVERITY_MEDIUM:       return "MEDIUM";
					case GL_DEBUG_SEVERITY_HIGH:         return "HIGH";

					default:                             throw std::invalid_argument{ "Invalid severity!" };
				}
			}();

			std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
		}
		static void _windowErrorCallback(int error, const char* description)
		{
			std::cout << std::format("Error ({0}): {1}", error, description);
		};

		GLFWwindow* m_nativeWindow{};
	};
}
