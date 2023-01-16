#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

#include "Helix/Rendering/Context/RenderContext.hpp"

namespace hlx
{
	class Window
	{
	public:
		enum class DisplayMode
		{
			Windowed,
			Borderless,
			Fullscreen
		};
		struct Properties
		{
		public:
			Properties() = default;
			Properties(std::string_view title, const glm::uvec2& dimensions)
				: title(title), dimensions(dimensions) {}

			std::string title{};
			glm::vec2   dimensions{};
			DisplayMode displayMode{ DisplayMode::Windowed };
		};
		using NativeWindow = void*;

		virtual ~Window() = default;

		static std::shared_ptr<Window> create(const Window::Properties& properties);

		virtual void refresh() = 0;
		virtual void rename(std::string_view title) = 0;
		virtual void resize(const glm::vec2& dimensions) = 0;
		virtual void switch_mode(const DisplayMode& displayMode) = 0;

		const Window::Properties& properties();
		virtual NativeWindow native_window() const = 0;

	protected:
		Window(const Window::Properties& properties);

		Properties m_properties{};
		NativeWindow m_nativeWindow{};
	};
}
