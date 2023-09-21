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

		void stage(const std::shared_ptr<Shader> shader) override;

		GLuint id() const
		{
			return m_id;
		}

		const std::shared_ptr<Shader> shader(Shader::Stage stage) const override;

	private:
        GLuint m_id{};

        std::array<std::shared_ptr<OpenGLShader>, 5> m_shaders{};
	};
}
