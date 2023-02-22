#pragma once

#include "Helix/Core/RenderAPI.hpp"

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
			static inline RenderAPI renderAPI{ RenderAPI::OpenGL };
		};
	};
}
