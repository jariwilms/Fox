#pragma once

#include "stdafx.hpp"

namespace hlx
{
	class Entry
	{
	public:
		Entry(const std::filesystem::path& path)
			: m_path{ path }, m_name{ m_path.filename().string() }
		{

		}

		const std::filesystem::path& path() const
		{
			return m_path;
		}
		std::string_view name() const
		{
			return m_name;
		}

	protected:
		std::filesystem::path m_path{};
		std::string m_name{};
	};
}
