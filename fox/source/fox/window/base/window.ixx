export module fox.window.base;

export namespace fox::interface::api
{
    class window
    {
	public:
		enum class mode_e
		{
			windowed  , 
			borderless, 
			fullscreen, 
		};
    };
}
