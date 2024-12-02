#pragma once

#include "stdafx.hpp"

#include "Fox/Window/Window.hpp"
//#include "Fox/Rendering/API/OpenGL/Context/OpenGLRenderContext.hpp"
#include "Fox/Input/Handler/Platform/GLFWInputHandler.hpp"
#include "Fox/Input/Input.hpp"
#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"

namespace fox
{
	class GLFWWindow : public Window
	{
	public:
        struct UserPointer
        {
		public:
			std::shared_ptr<GLFWWindow>          glfwWindow{};
			//std::shared_ptr<OpenGLRenderContext> renderContext{};              //TODO: abstract away from OpenGL + unique ptrs
			std::shared_ptr<GLFWInputHandler>    inputHandler{};
        };

		GLFWWindow(const std::string& title, const Vector2u& dimensions);
		~GLFWWindow() override;

		void refresh() override;

		void rename(const std::string& title) override;
		void resize(const Vector2f& dimensions) override;

        void glfw_error_callback(int error, const char* description);

	private:
		GLFWwindow* m_glfwWindow{};
		std::shared_ptr<UserPointer> m_userPointer{};
	};
}
