#pragma once

#include "stdafx.hpp"

namespace fox
{
	struct Relationship
	{
		std::optional<fox::id_t> parent{};
		std::vector  <fox::id_t> children{};
	};
}
