#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Rendering/Context/RenderContext.hpp"
#include "Helix/Input/Handler/InputHandlerAPI.hpp"

namespace hlx
{
	using NativeWindow = void;

	class Window
	{
	public:
		enum class DisplayMode
		{
			Windowed,
			Borderless,
			Fullscreen
		};

		virtual ~Window() = default;

		static std::shared_ptr<Window> create(const std::string& title, const glm::uvec2& dimensions);

		virtual void refresh() = 0;

		virtual void rename(const std::string& title) = 0;
		virtual void resize(const glm::vec2& dimensions) = 0;

		static NativeWindow* native_window();                                  //TODO: remove static method => request window from application class

	protected:
		Window(const std::string& title, const glm::uvec2& dimensions);

        std::string m_title{};
        glm::vec2   m_dimensions{};
        DisplayMode m_displayMode{ DisplayMode::Windowed };

		static inline NativeWindow* s_nativeWindow{};
	};
}
