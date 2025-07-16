module;

#include <fox/rendering/base/sampler/sampler.hpp>

export module fox.rendering.api.opengl.sampler;

import fox.rendering.api.opengl;
import fox.rendering.api.opengl.texture;

export namespace fox::gfx::api::gl
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
