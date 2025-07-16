export module fox.ecs.components.relationship;

import std;

import fox.core.types;

export namespace fox
{
	struct Relationship
	{
		std::optional<fox::id_t> parent{};
		std::vector  <fox::id_t> children{};
	};
}
