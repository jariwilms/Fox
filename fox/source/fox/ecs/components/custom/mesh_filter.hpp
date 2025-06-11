#pragma once

#include <memory>

#include <fox/rendering/mesh/mesh.hpp>
#include <fox/rendering/material/material.hpp>

namespace fox
{
	struct MeshFilter
	{
		std::shared_ptr<gfx::Mesh>     mesh{};
		std::shared_ptr<gfx::Material> material{};
	};
}
