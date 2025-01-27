#pragma once

#include "Fox/Core/Library/Camera/Camera.hpp"
#include "Fox/Core/Library/Component/MeshFilter.hpp"
#include "Fox/Core/Library/Component/Relationship.hpp"
#include "Fox/Core/Library/Transform/Transform.hpp"
#include "Fox/ECS/Components/Component.hpp"

namespace fox::cmp
{
	using CameraComponent       = cmp::Component<fox::Camera>;
	using MeshFilterComponent   = cmp::Component<fox::MeshFilter>;
	using RelationshipComponent = cmp::Component<fox::Relationship>;
	using TransformComponent    = cmp::Component<fox::Transform>;
}
