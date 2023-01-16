#pragma once

#include "stdafx.hpp"

#include "Entry.hpp"
#include "File.hpp"

namespace hlx
{
	class Directory : public Entry
	{
	public:
		explicit Directory(const std::filesystem::path& path)
			: Entry{ path }
		{
			const auto valid = std::filesystem::is_directory(path) && std::filesystem::exists(path);
			if (!valid) throw std::invalid_argument{ "The given path is not valid!" };
		}

		void refresh()
		{
			//update values
			//recursively refresh children as well
			//explore
		}

		Directory& create_directory(std::string_view name)
		{

		}
		File& create_file(std::string_view name)
		{

		}

		void delete_directory(std::string_view name)
		{
			//TODO: single directory string
			//TODO: string with subdir => "assets/models" deletes models
			//TODO: confirmation in program if multiple or directory not empty
		}
		void delete_file(std::string_view name)
		{

		}

		size_t count() const
		{
			return 0;
			//Returns amount of children (recursive?)
		}

	private:
		void explore()
		{
			
		}

		std::vector<std::shared_ptr<Entry>> m_children{};
		size_t m_count{};
	};
}
