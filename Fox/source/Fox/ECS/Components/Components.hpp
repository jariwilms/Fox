#pragma once

#include <fox/core/types/rendering/camera/camera.hpp>
#include <fox/core/transform/transform.hpp>
#include <fox/ecs/components/component.hpp>
#include <fox/ecs/components/custom/mesh_filter.hpp>
#include <fox/ecs/components/custom/relationship.hpp>

namespace fox::ecs
{
	using CameraComponent       = ecs::Component<fox::Camera>;
	using MeshFilterComponent   = ecs::Component<fox::MeshFilter>;
	using RelationshipComponent = ecs::Component<fox::Relationship>;
	using TransformComponent    = ecs::Component<fox::Transform>;
}
