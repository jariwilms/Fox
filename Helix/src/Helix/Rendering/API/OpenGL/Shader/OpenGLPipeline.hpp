#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Shader/Pipeline.hpp"
#include "OpenGLShader.hpp"

namespace hlx
{
	class OpenGLPipeline : public Pipeline
	{
	public:
		OpenGLPipeline();
		OpenGLPipeline(std::initializer_list<std::shared_ptr<Shader>> shaders);
		~OpenGLPipeline();

		void bind() const override;
		void unbind() const override;
		bool is_bound() const override;

		void stage(std::shared_ptr<Shader> shader) override;

        void forward(std::string_view identifier, const bool& value)      override;
        void forward(std::string_view identifier, const int& value)       override;
        void forward(std::string_view identifier, const float& value)     override;
        void forward(std::string_view identifier, const glm::vec2& value) override;
        void forward(std::string_view identifier, const glm::vec3& value) override;
        void forward(std::string_view identifier, const glm::vec4& value) override;
        void forward(std::string_view identifier, const glm::mat2& value) override;
        void forward(std::string_view identifier, const glm::mat3& value) override;
        void forward(std::string_view identifier, const glm::mat4& value) override;

		void forward_uniform(std::string_view identifier, size_t size, const void* data) override;

	protected:
		GLint uniform_location(std::string_view identifier);
	};
}
