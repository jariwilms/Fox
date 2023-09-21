#pragma once

#include "stdafx.hpp"

#include "Shader.hpp"

namespace hlx
{
	class Pipeline
	{
	public:
		virtual ~Pipeline() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual bool is_bound() const = 0;

		virtual void stage(const std::shared_ptr<Shader> shader) = 0;
		
		const std::shared_ptr<Shader> shader(Shader::Stage stage) const
		{
			switch (stage)
			{
				case Shader::Stage::Vertex:                 return m_shaders.at(0);
				case Shader::Stage::TessellationControl:	return m_shaders.at(1);
				case Shader::Stage::TessellationEvaluation: return m_shaders.at(2);
				case Shader::Stage::Geometry:			    return m_shaders.at(3);
				case Shader::Stage::Fragment:			    return m_shaders.at(4);

				default: throw std::invalid_argument{ "Invalid stage!" };
			}
		}

	protected:
        Pipeline() = default;

        std::array<std::shared_ptr<Shader>, 5> m_shaders{};
	};
}
