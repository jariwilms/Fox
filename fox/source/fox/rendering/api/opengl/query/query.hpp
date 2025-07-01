#pragma once

#include <stdafx.hpp>

#include <fox/rendering/api/opengl/opengl.hpp>
#include <fox/rendering/base/query/query.hpp>

namespace fox::gfx::api::gl
{
	class Query : public api::Query, public gl::Object
	{
	public:
		Query(Target target)
			: api::Query{ target }
		{
			throw std::logic_error{ "The method or operation has not been implemented!" };

			//handle_ = gl::create_query(gl::map_query_target(target));
		}
		~Query()
		{
			gl::delete_query(handle_);
		}

	private:
	};
}
