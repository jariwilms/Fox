#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/RenderContextAPI.hpp"

namespace hlx
{
	class RenderContext
	{
	public:
		static std::shared_ptr<RenderContextAPI> create();

		static const RenderContextAPI::Attributes& attributes();

	private:
		static inline std::unique_ptr<RenderContextAPI> s_renderContextAPI;
	};
}
