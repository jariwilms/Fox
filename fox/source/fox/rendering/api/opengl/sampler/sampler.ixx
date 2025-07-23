export module fox.rendering.api.opengl.sampler;

import fox.rendering.api.opengl;
import fox.rendering.api.opengl.texture;
import fox.rendering.base.sampler;

export namespace fox::gfx::api::gl
{
	class sampler : public gl::Object
	{
	public:
		using parameter_e = api::Sampler::Parameter;

		sampler()
			: gl::Object{ gl::create_sampler(), [](auto* handle) { gl::delete_sampler(*handle); } } {}

		void bind(gl::binding_t slot)
		{
			gl::bind_sampler(handle_, slot);
		}
	};
}
