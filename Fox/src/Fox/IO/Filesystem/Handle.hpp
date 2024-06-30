#pragma once

#include "stdafx.hpp"

#include "Entry.hpp"
#include "Directory.hpp"
#include "File.hpp"

namespace hlx
{
	class Handle
	{
	public:
		Handle(const std::filesystem::path& path)                              //TODO: single if statement?
		{
			const auto isDirectory = std::filesystem::is_directory(path);
			if (isDirectory) m_entryType = EntryType::Directory;
			else             m_entryType = EntryType::File;

			if (m_entryType == EntryType::Directory) m_entry = std::make_shared<Directory>(path);
			else                                     m_entry = std::make_shared<File>(path);
		}

		template<typename T>
		std::shared_ptr<T> promote()
		{
			static_assert(std::is_same<T, Directory>::value || std::is_same<T, File>::value, "Invalid Type!");

			return std::static_pointer_cast<T>(m_entry);
		}

		const std::filesystem::path& path() const
		{
			return m_entry->path();
		}
		std::string_view name() const
		{
			return m_entry->name();
		}

		template<Entry::Type T>
		bool is() const = delete;
		template<> 
		bool is<Entry::Type::Directory>() const
		{
			return m_entryType == Entry::Type::Directory;
		}
		template<> 
		bool is<Entry::Type::File>() const
		{
			return m_entryType == Entry::Type::File;
		}

	private:
		std::shared_ptr<Entry> m_entry;
		Entry::Type m_entryType;
	};
}
