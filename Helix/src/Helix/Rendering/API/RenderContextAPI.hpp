#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace hlx
{
	class RenderContextAPI
	{
	public:
		struct Attributes
		{
		public:
			Attributes() = default;
			//Attributes(std::string_view vendor, std::string_view renderer, std::string_view version)
				//: vendor{ vendor }, renderer{ renderer }, version{ version } {}
			
			const std::string vendor{};
			const std::string renderer{};
			const std::string version{};
		};

		virtual ~RenderContextAPI() = default;

		const RenderContextAPI::Attributes& attributes();

	protected:
		RenderContextAPI();

		//const Attributes m_attributes{};
	};
}
