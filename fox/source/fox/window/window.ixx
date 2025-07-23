export module fox.window;

import std;
import fox.core.meta;
import fox.core.types;
import fox.window.api;

export namespace fox::interface
{
	class window
	{
	public:
		using e_mode = api::window_t::e_mode;

		static auto create(const std::string& title, const fox::vector2u& dimensions) -> std::shared_ptr<interface::window>
		{
			return std::make_shared<meta::from_inaccessible_ctor<interface::window>>(std::in_place_t{}, title, dimensions);
		}

		void poll_events ()
		{
			_->poll_events();
		}
		void swap_buffers()
		{
			_->swap_buffers();
		}

		void rename      (const std::string  & title     )
		{
			_->rename(title);
		}
		void resize      (const fox::vector2u& dimensions)
		{
			_->resize(dimensions);
		}
		
		void        close() const
		{
			_->close();
		}
		auto should_close() const -> fox::bool_t
		{
			return _->should_close();
		}

		auto impl        () const -> std::shared_ptr<api::window_t>
		{
			return _;
		}

	protected:
		window(const std::string& title, const fox::vector2u& dimensions)
			: _{ std::make_shared<api::window_t>(title, dimensions) } {}

	private:
		std::shared_ptr<api::window_t> _;
	};
}
