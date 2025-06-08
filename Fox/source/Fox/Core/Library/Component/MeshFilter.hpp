#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/Mesh/Mesh.hpp"
#include "Fox/Rendering/Material/Material.hpp"

namespace fox
{
	struct MeshFilter
	{
		std::shared_ptr<gfx::Mesh>     mesh{};
		std::shared_ptr<gfx::Material> material{};
	};
}
