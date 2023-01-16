#pragma once

namespace hlx
{
	class Config
	{
	public:
		class Core
		{

		};

		class Rendering
		{
			enum class RenderAPI
			{
				DirectX,
				OpenGL,
				Vulkan,
			};

			static inline RenderAPI renderAPI{ RenderAPI::OpenGL };
		};
	};
}
