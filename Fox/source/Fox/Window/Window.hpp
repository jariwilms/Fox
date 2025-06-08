#pragma once

#include "stdafx.hpp"

#include "Fox/Input/Handler/InputHandlerAPI.hpp"

namespace fox::wnd::api
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

        NativeWindow* const native_handle() const
        {
            return m_nativeWindow;
        }

	protected:
		Window(const std::string& name, const fox::Vector2u& dimensions)
			: m_name{ name }, m_dimensions{ dimensions }, m_displayMode{ Mode::Windowed } {}

        std::string   m_name{};
        fox::Vector2f m_dimensions{};
        Mode          m_displayMode{};

		NativeWindow* m_nativeWindow{};
	};
}
