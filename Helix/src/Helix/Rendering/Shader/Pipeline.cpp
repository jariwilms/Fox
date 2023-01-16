#include "stdafx.hpp"

#include "Pipeline.hpp"
#include "Helix/Rendering/API/OpenGL/Shader/OpenGLPipeline.hpp"

namespace hlx
{
	std::shared_ptr<Pipeline> Pipeline::create()
	{
		return std::make_shared<OpenGLPipeline>();
	}
	std::shared_ptr<Pipeline> Pipeline::create(std::initializer_list<std::shared_ptr<Shader>> shaders)
	{
		return std::make_shared<OpenGLPipeline>(shaders);
	}
}
