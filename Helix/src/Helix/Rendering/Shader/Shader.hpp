#pragma once

#include "stdafx.hpp"

namespace hlx
{
	class Shader
	{
	public:
		enum class Stage
		{
			Vertex,
			TessellationControl, 
			TessellationEvaluation, 
			Geometry,
			Fragment,

			Compute, 
		};

		virtual ~Shader() = default;

		Stage stage() const
		{
			return m_stage;
		}

	protected:
		Shader(Stage stage)
			: m_stage{ stage } {}

		Stage m_stage{};
	};
}
