#pragma once

#include "stdafx.hpp"

#include "Helix/Core/RenderAPI.hpp"
#include "Helix/Rendering/Context/RenderContext.hpp"
#include "Helix/Input/Handler/InputHandlerAPI.hpp"

namespace hlx
{
	using NativeWindow = void;

	class Window
	{
	public:
		enum class Mode
		{
			Windowed,
			Borderless,
			Fullscreen
		};

		virtual ~Window() = default;

		static std::shared_ptr<Window> create(const std::string& title, const Vector2u& dimensions);

		virtual void refresh() = 0;

		virtual void rename(const std::string& title) = 0;
		virtual void resize(const Vector2f& dimensions) = 0;

		static NativeWindow* native_window();                                  //TODO: remove static method => request window from application class

	protected:
		Window(const std::string& title, const Vector2u& dimensions);

        std::string m_title{};
        Vector2f    m_dimensions{};
        Mode        m_displayMode{};

		static inline NativeWindow* s_nativeWindow{};                          //TODO: make not static
	};
}
