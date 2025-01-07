#pragma once

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/Sampler/Sampler.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/Texture.hpp"

namespace fox::gfx::api::gl
{
	class Sampler : public api::Sampler, public gl::Object
	{
	public:
		Sampler()
		{
			m_handle = gl::create_sampler();
		}
		Sampler(Sampler&& other) = default;
		~Sampler()
		{
			gl::delete_sampler(m_handle);
		}

		void bind(fox::uint32_t slot)
		{
			gl::bind_sampler(m_handle, slot);
		}

		Sampler& operator=(Sampler&& other) = default;

	private:
	};
}
