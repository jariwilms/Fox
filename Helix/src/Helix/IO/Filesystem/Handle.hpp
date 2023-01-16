#pragma once

#include "stdafx.hpp"

#include "Entry.hpp"
#include "Directory.hpp"
#include "File.hpp"
#include "Helix/Core/Library/Semantics/NonCopyable.hpp"

namespace hlx
{
	class Handle : public NonCopyable
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

		template<typename T>
		bool is() const
		{

		}
		template<> bool is<Directory>() const
		{
			return m_entryType == EntryType::Directory;
		}
		template<> bool is<File>() const
		{
			return m_entryType == EntryType::File;
		}

	private:
		enum class EntryType
		{
			Directory,
			File, 

			SymbolicLink, 
			HardLink, 
		};

		std::shared_ptr<Entry> m_entry;
		EntryType m_entryType;
	};
}
