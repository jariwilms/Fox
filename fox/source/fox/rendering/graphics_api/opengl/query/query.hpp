#pragma once

#include <stdafx.hpp>

#include <fox/rendering/api/query/query.hpp>
#include <fox/rendering/graphics_api/opengl/opengl.hpp>

namespace fox::gfx::api::gl
{
	class Query : public api::Query, public gl::Object
	{
	public:
		Query(Target target)
			: api::Query{ target }
		{
			throw std::logic_error{ "The method or operation has not been implemented!" };

			//m_handle = gl::create_query(gl::map_query_target(target));
		}
		~Query()
		{
			gl::delete_query(m_handle);
		}

	private:
	};
}
