#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Shader/Shader.hpp"

namespace hlx
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(Type type, const std::span<byte>& binary);
		~OpenGLShader();

        void forward(const std::string& identifier, const bool&      value) override;
        void forward(const std::string& identifier, const int&       value) override;
        void forward(const std::string& identifier, const float&     value) override;
        void forward(const std::string& identifier, const glm::vec2& value) override;
        void forward(const std::string& identifier, const glm::vec3& value) override;
        void forward(const std::string& identifier, const glm::vec4& value) override;
        void forward(const std::string& identifier, const glm::mat2& value) override;
        void forward(const std::string& identifier, const glm::mat3& value) override;
        void forward(const std::string& identifier, const glm::mat4& value) override;

	private:
		GLenum m_internalStage{};

	};
}
