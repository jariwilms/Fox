#pragma once

#include "Fox/Rendering/API/Sampler/Sampler.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Texture/Texture.hpp"

namespace fox::gfx::api::gl
{
	class Sampler : public api::Sampler, public gl::Object
	{
	public:
		Sampler()
		{
			m_handle = gl::create_sampler();
		}
		Sampler(Sampler&&) noexcept = default;
		~Sampler()
		{
			gl::delete_sampler(m_handle);
		}

		void bind(fox::uint32_t slot)
		{
			gl::bind_sampler(m_handle, slot);
		}

		Sampler& operator=(Sampler&&) noexcept = default;
	};
}
