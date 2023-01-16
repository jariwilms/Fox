#pragma once

#include "stdafx.hpp"

namespace hlx
{
	class IBindable
	{
	public:
		virtual ~IBindable() = default;

		Id id() const
		{
			return m_id;
		}

		virtual void bind() const { throw std::logic_error("The method or operation is not implemented."); }
		virtual void unbind() const { throw std::logic_error("The method or operation is not implemented."); }
		virtual bool is_bound() const { throw std::logic_error("The method or operation is not implemented."); }

	protected:
		IBindable() = default;

		Id m_id{};
	};
}