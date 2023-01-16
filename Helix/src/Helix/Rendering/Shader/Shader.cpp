#include "stdafx.hpp"

#include "Shader.hpp"
#include "Helix/Rendering/API/OpenGL/Shader/OpenGLShader.hpp"

namespace hlx
{
	std::shared_ptr<Shader> Shader::create(Type type, std::string_view source)
	{
		return std::make_shared<OpenGLShader>(type, source);
	}
    std::shared_ptr<Shader> Shader::create(Type type, const std::vector<byte>& source)
    {
		const auto* s = reinterpret_cast<const char*>(source.data());
		std::string_view view{ s, source.size() };

		return create(type, view);
    }

    bool Shader::valid() const
	{
		return m_valid;
	}
	std::string_view Shader::error() const
	{
		return m_error;
	}

	Shader::Type Shader::type() const
	{
		return m_type;
	}

	Shader::Shader(Type type)
		: m_type{ type } {}
}
