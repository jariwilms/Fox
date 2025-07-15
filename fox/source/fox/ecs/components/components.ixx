module;

#include <fox/rendering/camera/camera.hpp>

export module fox.ecs.components;

import fox.ecs.component;
import fox.ecs.components.mesh_filter;
import fox.ecs.components.relationship;
import fox.core.transform;

export namespace fox::ecs
{
	using CameraComponent       = ecs::Component<fox::Camera>;
	using MeshFilterComponent   = ecs::Component<fox::MeshFilter>;
	using RelationshipComponent = ecs::Component<fox::Relationship>;
	using TransformComponent    = ecs::Component<fox::Transform>;
}
