export module fox.ecs.component;

import std;
import fox.ecs.entity;

export namespace fox::ecs
{
	template<typename T>
	class Component
	{
	public:
		Component(const ecs::Entity& owner)
			: owner_{ owner }, value_{} {}
		Component(const ecs::Entity& owner, const T& value)
			: owner_{ owner },  value_{ value } {}
		template<typename... Args>
		Component(const ecs::Entity& owner, Args... args)
 			: owner_{ owner }, value_{ std::forward<Args>(args)... } {}

		auto owner() -> ecs::Entity&
		{
			return owner_;
		}
		auto owner() const -> const ecs::Entity&
		{
			return owner_;
		}

		auto get() -> T&
		{
			return value_;
		}
		auto get() const -> const T&
		{
			return value_;
		}

		operator T&()
		{
			return value_;
		}
		operator T&() const
		{
			return value_;
		}

	private:
		ecs::Entity owner_;
		T           value_;
	};
}
