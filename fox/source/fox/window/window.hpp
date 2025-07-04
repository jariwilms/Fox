#pragma once

#include <fox/window/api/api.hpp>

namespace fox::interface
{
	class Window
	{
	public:
		using Mode = impl::window_t::Mode;

		static auto create(const std::string& name, const fox::Vector2u& dimensions)
		{
			return std::shared_ptr<Window>{ new Window{ name, dimensions } };
		}

		void poll_events ()
		{
			_->poll_events();
		}
		void swap_buffers()
		{
			_->swap_buffers();
		}

		void rename(const std::string  & title     )
		{
			_->rename(title);
		}
		void resize(const fox::Vector2u& dimensions)
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

		auto impl() const
		{
			return _;
		}

	private:
		Window(const std::string& name, const fox::Vector2u& dimensions)
			: _{ std::make_shared<impl::window_t>(name, dimensions) } {}

		std::shared_ptr<impl::window_t> _{};
	};
}
