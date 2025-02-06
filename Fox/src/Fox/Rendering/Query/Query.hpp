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

		Target m_target{};
	};
}
