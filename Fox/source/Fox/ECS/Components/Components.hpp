#pragma once

#include "Fox/Core/Library/Camera/Camera.hpp"
#include "Fox/Core/Library/Component/MeshFilter.hpp"
#include "Fox/Core/Library/Component/Relationship.hpp"
#include "Fox/Core/Library/Transform/Transform.hpp"
#include "Fox/ECS/Components/Component.hpp"

namespace fox::ecs
{
	using CameraComponent       = ecs::Component<fox::Camera>;
	using MeshFilterComponent   = ecs::Component<fox::MeshFilter>;
	using RelationshipComponent = ecs::Component<fox::Relationship>;
	using TransformComponent    = ecs::Component<fox::Transform>;
}
