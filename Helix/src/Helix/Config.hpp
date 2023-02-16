#pragma once

namespace hlx
{
	class Config
	{
	public:
		void init()
		{

		}

		class Core
		{
		public:
		};

		class IO
		{
		public:
			static inline bool flipImages{ true };
		};

		class Rendering
		{
		public:
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
