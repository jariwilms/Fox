#pragma once

#include <stdafx.hpp>

namespace fox::io
{
	class Entry
	{
	public:
		auto path() const -> const std::filesystem::path&
		{
			return m_path;
		}
		auto name() const -> const std::filesystem::path&
		{
			return m_name;
		}

	protected:
		explicit Entry(const std::filesystem::path& path)
			: m_path{ path.lexically_normal() }, m_name{ m_path.filename() } {}

		std::filesystem::path m_path{};
		std::filesystem::path m_name{};
	};
}
