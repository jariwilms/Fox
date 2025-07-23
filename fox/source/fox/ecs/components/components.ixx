export module fox.ecs.components;

import fox.core.transform;
import fox.ecs.component;
import fox.ecs.components.mesh_filter;
import fox.ecs.components.relationship;
import fox.rendering.camera;

export namespace fox::ecs
{
	using camera_component       = ecs::component<fox::Camera>;
	using mesh_filter_component  = ecs::component<fox::mesh_filter>;
	using relationship_component = ecs::component<fox::relationship>;
	using transform_component    = ecs::component<fox::transform>;
}
