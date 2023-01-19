#pragma once

#include "stdafx.hpp"

#include "Shader.hpp"
#include "Helix/Rendering/Interface/IBindable.hpp"
#include "Helix/Core/Library/Semantics/NonCopyable.hpp"

namespace hlx
{
	class Pipeline : public IBindable, public NonCopyable
	{
	public:
		virtual ~Pipeline() = default;

		virtual void stage(const std::shared_ptr<Shader> shader) = 0;
		
		std::shared_ptr<Shader> shader(Shader::Type type) const
		{
			switch (type)
			{
				case Shader::Type::Vertex:                 return m_shaders[0];
				case Shader::Type::TessellationControl:	   return m_shaders[1];
				case Shader::Type::TessellationEvaluation: return m_shaders[2];
				case Shader::Type::Geometry:			   return m_shaders[3];
				case Shader::Type::Fragment:			   return m_shaders[4];

				default:								   throw std::invalid_argument{ "Invalid stage!" };
			}
		}

	protected:
        Pipeline() = default;

        std::array<std::shared_ptr<Shader>, 5> m_shaders{};
	};
}
