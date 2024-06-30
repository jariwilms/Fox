#pragma once

#include "stdafx.hpp"

namespace fox
{
	class Entry
	{
	public:
		enum class Type
		{
			File, 
			Directory, 

            SymbolicLink,
            HardLink,
		};

		Entry(const Entry&) = delete;
		virtual ~Entry() = default;

		static bool exists(const std::filesystem::path& path)
		{
			return std::filesystem::exists(path);
		}

		const std::filesystem::path& path() const
		{
			return m_path;
		}
		const std::filesystem::path& name() const
		{
			return m_name;
		}

		Entry& operator=(const Entry&) = delete;

	protected:
		explicit Entry(const std::filesystem::path& path)
		{
            m_path = path.lexically_normal();
            m_name = m_path.filename();
		}

		std::filesystem::path m_path{};
		std::filesystem::path m_name{};
	};
}
