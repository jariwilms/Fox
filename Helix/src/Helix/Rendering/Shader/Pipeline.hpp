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

		virtual void stage(const std::shared_ptr<Shader> shader) = 0;
		
		virtual const std::shared_ptr<Shader> shader(Shader::Stage stage) const = 0;

	protected:
        Pipeline() = default;
	};
}
