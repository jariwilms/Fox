export module fox.rendering.base.query;

export namespace fox::gfx::api
{
	class Query
	{
	public:
		enum class Target
		{
			Occlusion, 
			Statistics, 
			Timestamp, 
		};
	};
}
