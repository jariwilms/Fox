#pragma once

#include <stdafx.hpp>

namespace fox::io
{
	class Entry
	{
	public:
		auto path() const -> const std::filesystem::path&
		{
			return path_;
		}
		auto name() const -> const std::filesystem::path&
		{
			return name_;
		}

	protected:
		explicit Entry(const std::filesystem::path& path)
			: path_{ path.lexically_normal() }, name_{ path_.filename() } {}

		std::filesystem::path path_{};
		std::filesystem::path name_{};
	};
}
