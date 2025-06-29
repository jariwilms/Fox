#pragma once

#include <fox/rendering/api/sampler/sampler.hpp>
#include <fox/rendering/graphics_api/opengl/opengl.hpp>
#include <fox/rendering/graphics_api/opengl/texture/texture.hpp>

namespace fox::gfx::api::gl
{
	class Sampler : public api::Sampler, public gl::Object
	{
	public:
		Sampler()
		{
			m_handle = gl::create_sampler();
		}
		~Sampler()
		{
			gl::delete_sampler(m_handle);
		}

		void bind(gl::binding_t slot)
		{
			gl::bind_sampler(m_handle, slot);
		}
	};
}
