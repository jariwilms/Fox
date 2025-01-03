#pragma once

#include "stdafx.hpp"

namespace fox::gfx::api
{
	class Query
	{
	public:
		enum class Target
		{
			Occlusion, 
			Statistics, 
			Timestamp, 
		};

	protected:
		Query(Target target)
			: m_target{ target } {}
		Query(Query&& other) = default;
		~Query() = default;

		Query& operator=(Query&& other) = default;

		Target m_target{};
	};
}
