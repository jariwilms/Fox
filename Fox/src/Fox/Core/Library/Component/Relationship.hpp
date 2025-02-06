#pragma once

#include "stdafx.hpp"

#include "Fox/ECS/Types.hpp"

namespace fox
{
	struct Relationship
	{
	public:
		std::optional<ecs::id_t> parent{};
		std::vector<ecs::id_t>   children{};
	};
}
