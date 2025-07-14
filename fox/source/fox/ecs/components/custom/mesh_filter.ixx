module;

#include <fox/rendering/material/material.hpp>
#include <fox/rendering/mesh/mesh.hpp>

export module fox.ecs.components.mesh_filter;

import std;

export namespace fox
{
	struct MeshFilter
	{
		std::shared_ptr<gfx::Mesh>     mesh{};
		std::shared_ptr<gfx::Material> material{};
	};
}
