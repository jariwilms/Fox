#pragma once

#include <stdafx.hpp>

#include <fox/rendering/material/material.hpp>
#include <fox/rendering/mesh/mesh.hpp>

namespace fox
{
	struct MeshFilter
	{
		std::shared_ptr<gfx::Mesh>     mesh{};
		std::shared_ptr<gfx::Material> material{};
	};
}
