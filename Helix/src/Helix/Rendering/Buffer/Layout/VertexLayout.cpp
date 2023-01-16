#include "stdafx.hpp"

#include "VertexLayout.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/Layout/OpenGLVertexLayout.hpp"

namespace hlx
{
	std::shared_ptr<VertexLayout> VertexLayout::create()
	{
		return std::make_shared<OpenGLVertexLayout>();
	}
}
