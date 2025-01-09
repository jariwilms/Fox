#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/Query/Query.hpp"
#include "Fox/Rendering/API/OpenGL/Object/Object.hpp"

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

		Query(Query&& other) = default;
		~Query()
		{

		}

		Query& operator=(Query&& other) = default;

	private:
	};
}
