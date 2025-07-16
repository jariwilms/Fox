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

	protected:
		Query(Target target)
			: target_{ target } {}

		Target target_{};
	};
}
