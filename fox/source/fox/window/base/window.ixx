export module fox.window.base;

export namespace fox::interface::api
{
    class window
    {
	public:
		enum class e_mode
		{
			windowed  , 
			borderless, 
			fullscreen, 
		};
    };
}
