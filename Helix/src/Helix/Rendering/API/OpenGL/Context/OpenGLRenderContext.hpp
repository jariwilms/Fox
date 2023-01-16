#pragma once

#include "Helix/Rendering/API/RenderContextAPI.hpp"

namespace hlx
{
	class OpenGLRenderContext : public RenderContextAPI
	{
	public:
		OpenGLRenderContext();
		~OpenGLRenderContext() override;
	};
}
