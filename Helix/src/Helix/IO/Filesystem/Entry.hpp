#pragma once

#include "stdafx.hpp"

namespace hlx
{
	class Entry
	{
	public:
		Entry(const std::filesystem::path& path)
		{
			if (!std::filesystem::exists(path)) throw std::runtime_error{ "Path does not exist!" };

			m_path = path.lexically_normal();
			m_name = m_path.filename().string();
		}

		const std::filesystem::path& path() const
		{
			return m_path;
		}
		const std::filesystem::path& name() const
		{
			return m_name;
		}

	protected:
		std::filesystem::path m_path{};
		std::filesystem::path m_name{};
	};
}
