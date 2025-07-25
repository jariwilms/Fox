export module fox.rendering.api.opengl.query;

import std;
import fox.rendering.api.opengl;
import fox.rendering.base.query;

export namespace fox::gfx::api::gl
{
	class query : public gl::object
	{
	public:
		using target_e = api::query::target_e;

		explicit query(target_e target)
			: gl::object{ gl::create_query(gl::map_query_target(target)), [](auto* handle) { gl::delete_query(*handle); }}
			, target_{ target }
		{
			gl::todo();
		}

	private:
		target_e target_;
	};
}
