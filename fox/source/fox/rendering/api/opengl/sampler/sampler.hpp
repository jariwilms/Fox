#pragma once

#include <fox/rendering/api/opengl/opengl.hpp>
#include <fox/rendering/api/opengl/texture/texture.hpp>
#include <fox/rendering/base/sampler/sampler.hpp>

namespace fox::gfx::api::gl
{
	class Sampler : public api::Sampler, public gl::Object
	{
	public:
		Sampler()
		{
			handle_ = gl::create_sampler();
		}
		~Sampler()
		{
			gl::delete_sampler(handle_);
		}

		void bind(gl::binding_t slot)
		{
			gl::bind_sampler(handle_, slot);
		}
	};
}
