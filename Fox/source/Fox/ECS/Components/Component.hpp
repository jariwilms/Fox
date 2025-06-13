#pragma once

#include <fox/ecs/entity/entity.hpp>

namespace fox::ecs
{
	template<typename T>
	class Component
	{
	public:
		Component(const ecs::Entity& owner)
			: m_owner{ owner }, m_value{} {}
		Component(const ecs::Entity& owner, const T& value)
			: m_owner{ owner },  m_value{ value } {}
		template<typename... Args>
		Component(const ecs::Entity& owner, Args... args)
 			: m_owner{ owner }, m_value{ std::forward<Args>(args)... } {}

		auto owner() -> ecs::Entity&
		{
			return m_owner;
		}
		auto owner() const -> ecs::Entity const&
		{
			return m_owner;
		}

		auto get() -> T&
		{
			return m_value;
		}
		auto get() const -> T const&
		{
			return m_value;
		}

		operator T&()
		{
			return m_value;
		}
		operator T&() const
		{
			return m_value;
		}

	protected:
		ecs::Entity m_owner;
		T           m_value;
	};
}
