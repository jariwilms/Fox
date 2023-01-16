#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"

#include "Helix/Rendering/Shader/Shader.hpp"

namespace hlx
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(Type type, std::string_view source);
		~OpenGLShader();

	private:
		void log_error();

		GLenum m_internalType{};
	};
}
