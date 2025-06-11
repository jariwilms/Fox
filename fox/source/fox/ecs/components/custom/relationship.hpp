#pragma once

#include <optional>
#include <vector>

#include <fox/core/types/common/common.hpp>

namespace fox
{
	struct Relationship
	{
		std::optional<fox::id_t> parent{};
		std::vector  <fox::id_t> children{};
	};
}
