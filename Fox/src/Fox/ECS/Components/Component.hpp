#pragma once

#include "stdafx.hpp"

namespace fox::ecs
{
	class Entity;
}
namespace fox::cmp
{
	template<typename T>
	class Component
	{
	public:
		Component(const ecs::Entity& owner)
			: m_owner{ owner }, m_value{} {}
		template<typename... Args>
		Component(const ecs::Entity& owner, Args... args)
 			: m_owner{ owner }, m_value{ std::forward<Args>(args)... } {}
		Component(const ecs::Entity& owner, const T& value)
			: m_owner{ owner },  m_value{ value } {}

		      ecs::Entity& owner()
		{
			return m_owner;
		}
		const ecs::Entity& owner() const
		{
			return m_owner;
		}

		      T& get()
		{
			return m_value;
		}
		const T& get() const
		{
			return m_value;
		}

		operator T& ()
		{
			return m_value;
		}
		operator T& () const
		{
			return m_value;
		}

	protected:
		ecs::Entity m_owner;
		T           m_value;
	};
}
