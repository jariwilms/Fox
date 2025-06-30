#pragma once

namespace fox::interface::api
{
    class Window
    {
	public:
		enum class Mode
		{
			Windowed,
			Borderless,
			Fullscreen
		};
    };
}
