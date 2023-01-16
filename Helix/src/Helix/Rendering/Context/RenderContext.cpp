#include "stdafx.hpp"

#include "RenderContext.hpp"
#include "Helix/Rendering/API/OpenGL/Context/OpenGLRenderContext.hpp"

namespace hlx
{
	std::shared_ptr<RenderContextAPI> RenderContext::create()
	{
		return std::make_unique<OpenGLRenderContext>();
	}

	const hlx::RenderContextAPI::Attributes& RenderContext::attributes()
	{
		return s_renderContextAPI->attributes();
	}
}
