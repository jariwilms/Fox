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

    private:
		GLenum m_internalStage{};
	};
}
