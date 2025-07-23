export module fox.ecs.components.mesh_filter;

import std;
import fox.rendering.material;
import fox.rendering.mesh;

export namespace fox
{
	struct mesh_filter
	{
		std::shared_ptr<gfx::mesh>     mesh;
		std::shared_ptr<gfx::material> material;
	};
}
