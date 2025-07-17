export module fox.window.base;

export namespace fox::interface::api
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
