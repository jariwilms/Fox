export module fox.rendering.base.render_buffer;

export namespace fox::gfx::api
{
	struct render_buffer
	{
		enum class format_e
		{
            r8_unorm, 
            rg8_unorm, 
            rgb8_unorm, 
            rgba8_unorm, 
            rgba8_srgb, 
            d16_unorm, 
            d24_unorm, 
            d32_float, 
            d24_unorm_s8_uint, 
            d32_float_s8_uint, 
            s8_uint, 
		};
	};
}
