#pragma once

#include <stdafx.hpp>

#include <fox/rendering/api/opengl/opengl.hpp>
#include <fox/rendering/base/query/query.hpp>

namespace fox::gfx::api::gl
{
	class Query : public gl::Object
	{
	public:
		using Target = api::Query::Target;

		Query(Target target)
		{
			gl::todo();
		}
		~Query()
		{
			//gl::delete_query(handle_);
		}

	private:
		Target target_;
	};
}
