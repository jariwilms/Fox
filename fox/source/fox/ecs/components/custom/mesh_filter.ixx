export module fox.ecs.components.mesh_filter;

import std;

import fox.rendering.material;
import fox.rendering.mesh;

export namespace fox
{
	struct MeshFilter
	{
		std::shared_ptr<gfx::Mesh>     mesh{};
		std::shared_ptr<gfx::Material> material{};
	};
}
