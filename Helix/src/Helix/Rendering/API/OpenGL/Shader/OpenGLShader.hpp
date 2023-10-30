#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Shader/Shader.hpp"

namespace hlx
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(Stage stage, std::span<const byte> binary);
		~OpenGLShader();

		GLuint id()             const
		{
			return m_id;
		}
		GLenum internal_stage() const
		{
			return m_internalStage;
		}
		GLenum internal_type()  const
		{
			return m_internalType;
		}

    private:
		GLuint m_id{};
		GLenum m_internalStage{};
		GLenum m_internalType{};
	};
}
