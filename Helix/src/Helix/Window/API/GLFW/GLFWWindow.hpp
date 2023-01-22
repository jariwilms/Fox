#pragma once

#include "stdafx.hpp"

#include "Helix/Window/Window.hpp"
#include "Helix/Rendering/API/OpenGL/Context/OpenGLRenderContext.hpp"
#include "Helix/Input/Handler/Platform/GLFWInputHandler.hpp"
#include "Helix/Input/Input.hpp"

namespace hlx
{
	class GLFWWindow : public Window
	{
	public:
        struct UserPointer
        {
		public:
			std::shared_ptr<GLFWWindow>          glfwWindow{};
			std::shared_ptr<OpenGLRenderContext> renderContext{};              //TODO: abstract away from OpenGL
			std::shared_ptr<GLFWInputHandler>    inputHandler{};
        };

		GLFWWindow(const std::string& title, const glm::uvec2& dimensions);
		~GLFWWindow() override;

		void refresh() override;

		void rename(const std::string& title) override;
		void resize(const glm::vec2& dimensions) override;

        void glfw_error_callback(int error, const char* description);

	private:
		GLFWwindow* m_glfwWindow{};
		std::shared_ptr<UserPointer> m_userPointer{};
	};
}
