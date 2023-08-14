#pragma once

#include "stdafx.hpp"

#include "OpenGLShader.hpp"
#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Shader/Pipeline.hpp"

namespace hlx
{
	class OpenGLPipeline : public Pipeline
	{
	public:
		OpenGLPipeline();
		OpenGLPipeline(std::initializer_list<const std::shared_ptr<Shader>> shaders);
		~OpenGLPipeline();

		void bind() const override;
		void unbind() const override;
		bool is_bound() const override;

		void stage(const std::shared_ptr<Shader> shader) override;
	};
}
