export module fox.rendering.base.sampler;

export namespace fox::gfx::api
{
	class sampler
	{
	public:
        enum class parameter
        {
            border_color,
            compare_func,
            compare_mode,
            lod_bias,
            magnification_filter,
            maximum_lod,
            minification_filter,
            minimum_lod,
            wrapping_r,
            wrapping_s,
            wrapping_t,
        };
	};
}
