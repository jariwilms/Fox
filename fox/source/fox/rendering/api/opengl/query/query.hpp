#pragma once

#include <stdafx.hpp>

#include <fox/rendering/base/query/query.hpp>

import fox.rendering.api.opengl;
import fox.rendering.api.opengl.mapping;
import fox.rendering.api.opengl.object;

namespace fox::gfx::api::gl
{
	class Query : public gl::Object
	{
	public:
		using Target = api::Query::Target;

		Query(Target target)
			: gl::Object{ gl::create_query(gl::map_query_target(target)), [](auto* handle) { gl::delete_query(*handle); }}
			, target_{ target }
		{
			gl::todo();
		}

	private:
		Target target_;
	};
}
