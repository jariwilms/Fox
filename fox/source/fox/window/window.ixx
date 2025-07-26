export module fox.window;

import std;
import fox.api;
import fox.core.types;

export namespace fox::window
{
	void poll_events ()
	{
		fox::api::window->poll_events();
	}
	void swap_buffers()
	{
		fox::api::window->swap_buffers();
	}

	void rename      (const std::string  & title     )
	{
		fox::api::window->rename(title);
	}
	void resize      (const fox::vector2u& dimensions)
	{
		fox::api::window->resize(dimensions);
	}
		
	void        close()
	{
		fox::api::window->close();
	}
	auto should_close() -> fox::bool_t
	{
		return fox::api::window->should_close();
	}
}
