#pragma once

#include <fox/rendering/base/sampler/sampler.hpp>

import fox.rendering.api.opengl;
import fox.rendering.api.opengl.texture;

namespace fox::gfx::api::gl
{
	class Sampler : public gl::Object
	{
	public:
		using Parameter = api::Sampler::Parameter;

		 Sampler()
			: gl::Object{ gl::create_sampler(), [](auto* handle) { gl::delete_sampler(*handle); } } {}

		void bind(gl::binding_t slot)
		{
			gl::bind_sampler(handle_, slot);
		}
	};
}
